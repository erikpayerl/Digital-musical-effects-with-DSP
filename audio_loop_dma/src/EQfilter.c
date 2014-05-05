#include "ezdsp5535.h"
#include "ezdsp5535_led.h"
#include "stdio.h"

int EQfilter( void)
{
	Int16 i, j;
    
    printf("    User LED tests toggles each of the four user LEDs 3 times\n");
    EZDSP5535_LED_init( );

    /* Running LED test */
    for ( j = 0 ; j < 3 ; j++ )
    {
        for ( i = 0 ; i < 4 ; i++ )
        {
        	EZDSP5535_XF_toggle();
            if ( EZDSP5535_LED_on( i ) )  // Turn on user LED i
                return 1;
            EZDSP5535_waitusec( 100000 );
        }
        
        for ( i = 0 ; i < 4 ; i++ )
        {
        	EZDSP5535_XF_toggle();
            if ( EZDSP5535_LED_off( i ) ) // Turn off user LED i
                return 2;
            EZDSP5535_waitusec( 100000 );
        }
    }
    EZDSP5535_LED_setall( 0x00 );
	printf("EQfilter() Done! \n");
	return 0;
}
