#ifndef KEYS_H
    #define KEYS_H

    // Header of special characters
    #define EXT_ESC   27
    #define EXT_CSI   ((27<<16)+(91<<8))
    #define EXT_SS3   ((27<<16)+(79<<8))
    #define EXT_SPEC1 (194<<8)
    #define EXT_SPEC2 (195<<8)
    #define HDR_FN1   ((long)EXT_CSI+49)
    #define HDR_FN2   ((long)EXT_CSI+50)
    #define EXT_FN1   ((HDR_FN1<<16)+(126))
    #define EXT_FN2   ((HDR_FN2<<16)+(126))
    #define EXT_FN3   (1<<8)

    // Enum for all the key codes
    typedef enum {

        //---------------------------
        //---------- ASCII ----------
        //---------------------------
        KEY_NONE    = '\0',

        KEY_ESCAPE  = 27,
        KEY_TAB     = '\t',
        KEY_RETURN  = '\n',
        KEY_DELETE  = 127,
        KEY_SPACE   = ' ',

        KEY_ARROW_LEFT  = (EXT_CSI+68),
        KEY_ARROW_RIGHT = (EXT_CSI+67),
        KEY_ARROW_UP    = (EXT_CSI+65),
        KEY_ARROW_DOWN  = (EXT_CSI+66),

        KEY_F1  = (EXT_SS3+80),  
        KEY_F2  = (EXT_SS3+81),  
        KEY_F3  = (EXT_SS3+82),  
        KEY_F4  = (EXT_SS3+83),  
        KEY_F5  = (EXT_FN1+(53<<8)),
        KEY_F6  = (EXT_FN1+(55<<8)),
        KEY_F7  = (EXT_FN1+(56<<8)),
        KEY_F8  = (EXT_FN1+(57<<8)),
        KEY_F9  = (EXT_FN2+(48<<8)),
        KEY_F11 = (EXT_FN3+154),
        KEY_F12 = (EXT_FN2+(52<<8)),
        
        KEY_A   = 'A',
        KEY_B   = 'B',
        KEY_C   = 'C',
        KEY_D   = 'D',
        KEY_E   = 'E',
        KEY_F   = 'F',
        KEY_G   = 'G',
        KEY_H   = 'H',
        KEY_I   = 'I',
        KEY_J   = 'J',
        KEY_K   = 'K',
        KEY_L   = 'L',
        KEY_M   = 'M',
        KEY_N   = 'N',
        KEY_O   = 'O',
        KEY_P   = 'P',
        KEY_Q   = 'Q',
        KEY_R   = 'R',
        KEY_S   = 'S',
        KEY_T   = 'T',
        KEY_U   = 'U',
        KEY_V   = 'V',
        KEY_W   = 'W',
        KEY_X   = 'X',
        KEY_Y   = 'Y',
        KEY_Z   = 'Z',

        KEY_1   = '0',
        KEY_2   = '1',
        KEY_3   = '2',
        KEY_4   = '3',
        KEY_5   = '4',
        KEY_6   = '5',
        KEY_7   = '6',
        KEY_8   = '7',
        KEY_9   = '8',
        KEY_0   = '9',

        KEY_MINUS           = '-',
        KEY_EQUALS          = '=',
        KEY_LEFTBRACKET     = '[',
        KEY_RIGHTBRACKET    = ']',
        KEY_BACKSLASH       = '\\', 
        KEY_NONUSHASH       = '/', 
        KEY_SEMICOLON       = ';',
        KEY_APOSTROPHE      = '\'',
        KEY_GRAVE           = '`', 
        KEY_COMMA           = ',',
        KEY_PERIOD          = '.',
        KEY_SLASH           = '/',

        KEY_SQUARE    = (EXT_SPEC1+178), 
        KEY_AMPERSAND = '&',               
        KEY_E_ACUTE   = (EXT_SPEC2+169),
        KEY_QUOTE2    = '"', 
        KEY_QUOTE1    = '\'',
        KEY_E_GRAVE   = (EXT_SPEC2+168),
        KEY_C_CEDILLA = (EXT_SPEC2+167),
        KEY_A_GRAVE   = (EXT_SPEC2+160),
        KEY_DEGREES   = (EXT_SPEC1+176),         
        

        
/*

        KEY_PAGEUP       = 0,
        KEY_PAGEDOWN     = 0,


        KEY_HOME         = ((EXT_ESCAPE<<16)|(EXT_BRACKET<<8)|),
        KEY_END          = 0,
        KEY_INSERT       = 0, 


        KEY_PRINTSCREEN  = (70 | (1<<30)),
        KEY_SCROLLLOCK   = (71 | (1<<30)),
        KEY_PAUSE        = (72 | (1<<30)),
        KEY_DELETE       = (76 | (1<<30)),


        KEY_NONUSBACKSLASH = 100, 
        KEY_APPLICATION = 101, 
        KEY_POWER = 102, 
        KEY_KP_EQUALS = 103,

        KEY_KP_LEFTPAREN = 182,
        KEY_KP_RIGHTPAREN = 183,
        KEY_KP_LEFTBRACE = 184,
        KEY_KP_RIGHTBRACE = 185,
        KEY_KP_TAB = 186,
        KEY_KP_BACKSPACE = 187,
        KEY_KP_POWER = 195,
        KEY_KP_PERCENT = 196,

        KEY_KP_VERTICALBAR = 201,

        KEY_KP_COLON = 203,
        KEY_KP_HASH = 204,
        KEY_KP_SPACE = 205,
        KEY_KP_EXCLAM = 207,

        KEY_KP_PLUSMINUS = 215
        
   
        
//*/


    } KeyRGR;

#endif 
