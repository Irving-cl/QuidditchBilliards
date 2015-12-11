
#ifndef _QUIDDITCHCONSTANTS_H_
#define _QUIDDITCHCONSTANTS_H_

/// Mathematical constants
const float SQRT2 = 1.414f;
const float PI = 3.14159f;

/// Length, width, height constants
const float R = 0.5f;                                    // Radius of balls
const float TABLE_WIDTH = 20 * R;                        // Width of table
const float TABLE_LENGTH = 2 * TABLE_WIDTH;              // Length of table
const float TABLE_BASE_THICKNESS = 0.2f;                 // Thickness of table's base
const float TABLE_WALL_HEIGHT = 1.4 * R;                 // Height of table's wall
const float TABLE_LRWALL_LENGTH = TABLE_WIDTH - 6 * R;   // Length of table's left and right wall
const float TABLE_FBWALL_LENGTH = (TABLE_LENGTH - (6 + 2 * SQRT2) * R) / 2;    // Length of table's front and back wall
const float FLAG_ROLE_LENGTH = 7.5f;                     // Length of flag's role
const float FLAG_ROLE_RADIUS = 0.15f;                    // Radius of flag's role
const float CUE_LENGTH = 10.0f;                          // Length of the cue

/// Speed constants
const float CUE_ROTATE_SPEED = 1.0f;                     // Rotating speed of the que when we adjust the direction
const float CUE_HIT_SPEED = 0.15f;                       // Speed of the cue when we are hitting the ball
const float UPDOWN_SPEED = 0.03f;                        // Speed of golden ball when it is landing on the table

/// Time constants
const float FLY_TIME = 1.0f;                             // Time of golden ball flying above the table
const float UPDOWN_TIME = 0.75f;                         // Time the golden ball takes to land on the table
const float STOP_TIME = 0.5f;                            // Time the golden ball stays on the table for once

/// Others
const unsigned int NUM_TEXTURES = 8;                     // Number of textures required in the application
const float FLAG_PARAMETER = 10.0f;                      // Decides the size of the flag
const float GBALL_FLY_HEIGHT = 5.0f;                     // Height of the golden ball when it flys
const float CUE_ANGLE = -15.0f;                          // Angle of between the cue and the table plane
const float CUE_BALL_DISTANCE = 3.0f;                    // Distance between cue and ball before we hit
const GLushort LINE_PATTERN = 0xFFFF;                    // Pattern of line
const GLushort STIPPLE_PATTERN = 0x3333;                 // Pattern of stipple near the cue
const float STIPPLE_MOVEMENT = 0.005f;                   // Single movement of stipple
const float STIPPLE_MAX_MOVEMENT = 0.3f;                 // When it reaches max movement, the stipple movement will be reset to 0
const float GOLDEN_BALL_HEIGHT = 5.0f;                   // Height of golden ball when it is above the table

/// Positions constants
const float WALL_FRONT_BOUND = -TABLE_WIDTH / 2 + R;     // Front bound of the wall
const float WALL_BACK_BOUND = TABLE_WIDTH / 2 - R;       // Back bound of the wall
const float WALL_LEFT_BOUND = -TABLE_LENGTH / 2 + R;     // Left bound of the wall
const float WALL_RIGHT_BOUND = TABLE_LENGTH / 2 - R;     // Right bound of the wall

#endif // _QUIDDITCHCONSTANTS_H_