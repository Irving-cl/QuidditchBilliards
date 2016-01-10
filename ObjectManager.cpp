
#include "ObjectManager.h"

//===========================================================================//

ObjectManager::ObjectManager(CInputSystem * input)
{
	/// Initialize textures
	LoadTextures();                                            // Load textures from files
	m_TexturePool = new unsigned int[NUM_TEXTURES];            // New array
	m_NatureTexture = new NatureTexture();
	m_NatureTexture->GenerateTexture();                        // Generate a nature texture
	for (int i = 0; i < NUM_TEXTURES - 1; i++)
		m_TexturePool[i] = m_Textures[i].ID;                   // Give values
	m_TexturePool[NUM_TEXTURES - 1] = m_NatureTexture->ID;

	/* Note: Input system must be set before creating
	objects since cue will have input system memeber */
	m_Input = input;        // Set input

	/// Create objects
	CreateObjects();

	/// Create light
	SetLight();

	/// Set texture pool
	std::vector<OpenGLObject*>::iterator iter;
	for (iter = m_Objects.begin(); iter != m_Objects.end(); iter++)
	{
		(*iter)->SetTexturePool(m_TexturePool);
	}

	/// Set initial position
	SetInitialPosition();

	/// Give initial speed to wander balls
	for (int i = 9; i < 15; i++)
	{
		int direction = rand();
		((Ball *)m_Objects[i])->SetSpeed(Vector3(0.1f * cos(direction), 0.0f, 0.1f * sin(direction)));
	}
}

//===========================================================================//

ObjectManager::~ObjectManager()
{
	/// Delete objects
	std::vector<OpenGLObject*>::iterator iter;
	for (iter = m_Objects.begin(); iter != m_Objects.end(); iter++)
	{
		if (*iter != NULL)
		{
			delete (*iter);
			*iter = NULL;
		}
	}

	/// Delete textures
	delete[] m_TexturePool;                           // Delete texture pool
	for (int i = 0; i < NUM_TEXTURES - 1; i++)        // Free textures
	{
		m_Textures[i].FreeImage();
		glDeleteTextures(1, &m_Textures[i].ID);
	}

	/// Delete light
	if (m_Light)
		delete m_Light;

	m_Input = NULL;
}

//===========================================================================//

void ObjectManager::LoadTextures()
{
	char filename[128];
	char *bmpName[] = { "wood", "green_area", "ghost_ball", "wander_ball",
		"golden_ball", "main_ball", "cue", "sjtu", "wall", "flare" };
	for (int i = 0; i < NUM_TEXTURES - 1; i++)
	{
		sprintf(filename, "data/%s", bmpName[i]);
		strcat(filename, ".bmp");
		if (!m_Textures[i].Load(filename))
		{
			MessageBox(NULL, "装载位图文件失败！", "错误", MB_OK);
			exit(-1);
		}
	}
}

//===========================================================================//

void ObjectManager::CreateObjects()
{
	/// Create table
	Table * table = new Table();
	m_Objects.push_back(table);

	/// Create flag
	Flag * flag = new Flag();
	m_Objects.push_back(flag);

	/// Create balls
	MainBall * mainBall = new MainBall();              // Create one main ball
	m_Objects.push_back(mainBall);
	for (int i = 0; i < 6; i++)
	{
		GhostBall * ghostBall = new GhostBall();       // Create six ghost balls
		m_Objects.push_back(ghostBall);
	}
	for (int i = 0; i < 6; i++)
	{
		WanderBall * wanderBall = new WanderBall();    // Create six wander balls
		m_Objects.push_back(wanderBall);
	}
	GoldenBall * goldenBall = new GoldenBall();        // Create one golden ball
	m_Objects.push_back(goldenBall);

	/// Create cue
	Cue * cue = new Cue(mainBall);
	m_Objects.push_back(cue);
	cue->SetInput(m_Input);

	/// Create skybox(room scene)
	Room * room = new Room();
	room->SetPosition(Vector3(-ROOM_LENGTH / 2, -TABLE_PLANE_HEIGHT, -ROOM_LENGTH / 2));
	m_Objects.push_back(room);

	/// Create particle system
	m_ParticleSystem = new ParticleSystem();
	m_Objects.push_back(m_ParticleSystem);
}

//===========================================================================//

void ObjectManager::SetInitialPosition()
{
	m_Objects[1]->SetPosition(Vector3(12.0f, 0.0f, 12.0f));                      // Flag
	m_Objects[2]->SetPosition(Vector3(0.0f, TABLE_BASE_THICKNESS + R, 0.0f));    // Main ball
	for (int i = 0; i < 2; i++)    // Ghost balls
	{
		for (int j = 0; j < 3; j++)
		{
			((Ball *)m_Objects[i * 3 + j + 3])->SetIniPosition(
				Vector3(2 * R + j * 1.2f + 2.0f, TABLE_BASE_THICKNESS + R, i * 1.2f - R));

		}
	}
	for (int i = 0; i < 2; i++)    // Wander balls
	{
		for (int j = 0; j < 3; j++)
		{
			((Ball *)m_Objects[i * 3 + j + 9])->SetPosition(
				Vector3(-(2 * R + j * 1.2f + 2.0f), TABLE_BASE_THICKNESS + R, i * 1.2f - R));
		}
	}
	m_Objects[15]->SetPosition(Vector3(0.0f, TABLE_BASE_THICKNESS + R + GBALL_FLY_HEIGHT, 0.0f));    // Golden ball
}

//===========================================================================//

void ObjectManager::SetLight()
{
	m_Light = new Light();
	m_Light->Init();
	m_Light->SetInput(m_Input);
}

//===========================================================================//

void ObjectManager::Draw()
{
	glPushMatrix();
	{
		glTranslatef(0.0f, -2.0f, 0.0f);
		/// Draw all objects
		std::vector<OpenGLObject*>::iterator iter;
		for (iter = m_Objects.begin(); iter != m_Objects.end(); iter++)
		{
			(*iter)->Draw();
		}
	}
	glPopMatrix();
}

//===========================================================================//

void ObjectManager::Update()
{
	/// Update all objects
	std::vector<OpenGLObject*>::iterator iter;
	for (iter = m_Objects.begin(); iter != m_Objects.end(); iter++)
	{
		(*iter)->Update();
	}

	/// Update light
	m_Light->Update();

	/// Balls hit each other
	for (int i = 2; i < 14; i++)
	{
		for (int j = i + 1; j < 15; j++)
		{
			if (((Ball *)m_Objects[i])->CheckHit((Ball *)m_Objects[j]))
			{
				Vector3 position = (m_Objects[i]->GetPosition() + m_Objects[j]->GetPosition()) / 2.0f;
				m_ParticleSystem->GenerateExplosion(position);
			}
		}
	}
}