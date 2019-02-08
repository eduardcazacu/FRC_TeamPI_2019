/*
    In this file the code names for the hatch placing targets are defined. These are to be used throught the code
*/

/*
enum for the target:
code:   [GO]_[S][S2]_[L]
        GO = Game Object {R = Rocket, C = Cargo Ship,L = loading station}
        S = Side viewed from the Alliance Wall {L = Left, R= Right}
        S2 = extra side information viewed from the Alliance Wall {F = Front, B = Back}
        L = level counting from bottom (Rocket) closes to the Alliance wall (cargo ship) 
*/
typedef enum AutoTarget{
    NO_TARGET,
    //Left rocket
    R_LF1,
    R_LF2,
    R_LF3,
    //back:
    R_LB1,
    R_LB2,
    R_LB3,
    //right rocket
    R_RF1,
    R_RF2,
    R_RF3,
    //back:
    R_RB1,
    R_RB2,
    R_RB3,

    //cargo:
    C_LL1,
    C_LL2,
    C_LL3,
    //front
    C_LF1,
    C_RF1,
    //right side:
    C_RR1,
    C_RR2,
    C_RR3,

    //Loading stations:
    L_LL1,
    L_RR1

} AutoTarget;