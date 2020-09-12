/*
 ============================================================================
 Name        : IPv4 Validation: Validate an entered IP is valid IPv4 in C.
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
//#include "../../PublicInterfaces/commonIncludes.h"
#include <string.h>

#define MAX_IP_LEN 19
#define TRUE 1
#define FALSE 0

/* implementation 1 */
/**
 *
 * @param str
 * @return
 */
int isValidIp4 (char *str)
{
    int segs  = 0;   /* Segment count. */
    int chcnt = 0;  /* Character count within segment. */
    int accum = 0;  /* Accumulator for segment. */

    /* Catch NULL pointer. */
    if (str == NULL)
        return FALSE;

    /* Process every character in string. */
    while (*str != '\0')
    {
        /* Segment changeover. */
        if (*str == '.')
        {
            /* Must have some digits in segment. */
            if (chcnt == 0)
            {
                printf("1:chcnt is 0\n");
                return FALSE;
            }
            /* Limit number of segments. */
            if (++segs == 4)
            {
                printf("seg is less than 4\n");
                return FALSE;
            }

            /* Reset segment values and restart loop. */
            chcnt = accum = 0;
            str++;
            continue;
        }

        /* Check numeric. */
        if ((*str < '0') || (*str > '9'))
        {
            printf("not integer\n");
            return FALSE;
        }

        /* Accumulate and check segment. */
        if ((accum = accum * 10 + *str - '0') > 255)
        {
            printf("over 255\n");
            return FALSE;
        }

        /* Advance other segment specific stuff and continue loop. */
        chcnt++;
        str++;
    }

    /* Check enough segments and enough characters in last segment. */
    if (segs != 3)
    {
        printf("seg is not 3\n");
        return FALSE;
    }

    if (chcnt == 0)
    {
        printf("2:chcnt is 0\n");
        return FALSE;
    }

    /* Address okay. */
    return TRUE;
}

/* implementation 2 */
/**
 *
 * @param ip
 * @param text_reason
 * @return
 */
bool validIsIPv4Format(char *ip, char *text_reason)
{
    int i=0, j=MAX_IP_LEN, countDots = 0, ipLen = strlen(ip);
    int octet = 0;
    char tempIpAddr[MAX_IP_LEN];
    char ipAddr[MAX_IP_LEN];

    memset(tempIpAddr, '\0', MAX_IP_LEN);
    memset(ipAddr, '\0', MAX_IP_LEN);

    /* Save a local copy */
    strncpy(ipAddr, ip, MAX_IP_LEN);

    if ((ip == NULL) || (text_reason == NULL))
    {
        return FALSE;
    }

    /* Minimum length for IPv4 is 7 (0.0.0.0). */
    if (ipLen < 7)
    {
        strcpy(text_reason, "IP string length is too short, use valid IPv4 format (e.g 1.1.1.1).");
        return FALSE;
    }

    /* Can start or end with a period. */
    if((ip[0] == '.') || (ip[ipLen-1] == '.'))
    {
        strcpy(text_reason, "IP is not IPv4 format, period can't start or end.");
        return FALSE;
    }

    for(i=0; i<ipLen; i++)
    {
        if( (ip[i]<'0' || ip[i]>'9') && (ip[i] != '.') )
        {
            strcpy(text_reason, "IP is not IPv4 format, special character cannot be in IP string.");
            return FALSE;
        }

        if (ipAddr[i] == '.')
        {
            /* save index too to check for consecutive periods. note j cannot be initialized to 0. */
            if(i==(j+1))
            {
                strcpy(text_reason, "IP is not IPv4 format, Consecutive periods found.");
                return FALSE;
            }
            j=i;

            countDots++; /* count periods for IPv4 validation at the end of string parsing. */
            ipAddr[i] = '0';
            octet     = atoi(tempIpAddr);

            if ((octet < 0) || (octet > 255))
            {
                strcpy(text_reason, "IP octets cannot be less than 0 or over 255.");
                return FALSE;
            }

            strncpy(tempIpAddr, ipAddr, MAX_IP_LEN);
        }
        else
        {
            tempIpAddr[i] = ipAddr[i];
            ipAddr[i] = '0';
        }
    }

    /* Validate the last octet left in tempIpAddr */
    octet = atoi(tempIpAddr);
    if ((octet < 0) || (octet > 255))
    {
        strcpy(text_reason, "IP octets cannot be less than 0 or over 255.");
        return FALSE;
    }

    if (countDots != 3)
    {
        strcpy(text_reason, "IPv4 format requires three periods between 4 integers/octets (0-255).");
        return FALSE;
    }

    return TRUE;
}

/* Implementation 2: [optimization] Performance enhancement, Refactoring and Memoization */
/**
 *
 * @param ip
 * @param text_reason
 * @return
 */
bool validIsIPv4Format_v2(char *ip, char *text_reason)
{
    int i=0, countDots=0, ipLen=0;
    int octet = 0;
    char tempIpAddr[MAX_IP_LEN];
    char ipAddr[MAX_IP_LEN];

    memset(tempIpAddr, '\0', MAX_IP_LEN);
    memset(ipAddr, '\0', MAX_IP_LEN);

    if ((ip == NULL) || (text_reason == NULL))
    {
        return FALSE;
    }

    /* Save a local copy */
    strncpy(ipAddr, ip, MAX_IP_LEN);
    ipLen = strlen(ip);

    /* Minimum length for IPv4 is 7 (0.0.0.0). */
    if (ipLen < 7)
    {
        strcpy(text_reason, "IP string length is too short, use valid IPv4 format (e.g 1.1.1.1).");
        return FALSE;
    }

    /* Can start or end with a period. */
    if((ip[0] == '.') || (ip[ipLen-1] == '.'))
    {
        strcpy(text_reason, "IP is not IPv4 format, period can't start or end.");
        return FALSE;
    }

    for(i=0; i<ipLen; i++)
    {
        if( (ip[i]<'0' || ip[i]>'9') && (ip[i] != '.') )
        {
            strcpy(text_reason, "IP is not IPv4 format, special character cannot be in IP string.");
            return FALSE;
        }

        if (ipAddr[i] == '.')
        {
            /* save index too to check for consecutive periods. note j cannot be initialized to 0. */
            if(ipAddr[i+1] == '.')
            {
                strcpy(text_reason, "IP is not IPv4 format, Consecutive periods found.");
                return FALSE;
            }

            countDots++; /* count periods for IPv4 validation at the end of string parsing. */
            ipAddr[i] = '0';
            octet     = atoi(tempIpAddr);

            if ((octet < 0) || (octet > 255))
            {
                strcpy(text_reason, "IP octets cannot be less than 0 or over 255.");
                return FALSE;
            }

            strncpy(tempIpAddr, ipAddr, MAX_IP_LEN);
        }
        else
        {
            tempIpAddr[i] = ipAddr[i];
            ipAddr[i] = '0';
        }
    }

    /* Validate the last octet left in tempIpAddr */
    octet = atoi(tempIpAddr);
    if ((octet < 0) || (octet > 255))
    {
        strcpy(text_reason, "IP octets cannot be less than 0 or over 255.");
        return FALSE;
    }

    if (countDots != 3)
    {
        strcpy(text_reason, "IPv4 format requires three periods between 4 integers/octets (0-255).");
        return FALSE;
    }

    return TRUE;
}

/* Implementation 3:  the calling function must contain a terminating string in the char array */
/**
 *
 * @param ipAddr
 * @param text_reason
 * @return
 */
bool isIPvalidIPv4Format(char *ipAddr, char *text_reason)
{
    int octet       = 0;
    int cntPrds      = 0;
    bool octetValid = FALSE;

    if (ipAddr==NULL || text_reason==NULL)
    {
        strcpy(text_reason, "null pointer error.");
        return FALSE;
    }

    int ipLen=strlen(ipAddr); /* get length of IP for quick checks before looping. */

    /* Cannot start or end with a period. */
    if(ipAddr[0]=='.' || ipAddr[ipLen-1]=='.')
    {
        strcpy(text_reason, "IPv4 format error: Leading or trailing period.");
        return FALSE;
    }

    /* Min length for IPv4 is 7 (0.0.0.0) and max is 15 (255.255.255.255). */
    if (ipLen<7 || ipLen>15)
    {
        strcpy(text_reason, "IPv4 format error: Length of IP is not within range (0.0.0.0-255.255.255.255).");
        return FALSE;
    }

    while (*ipAddr != '\0')
    {
        if(*ipAddr=='.')
        {
            cntPrds++; /* found a period in string, keep count */

            if (!octetValid)
            {
                strcpy(text_reason, "IPv4 format error: Consecutive periods");
                return FALSE;
            }

            /* no need to continue with loop, too many octets/periods */
            if (cntPrds==4)
            {
                strcpy(text_reason, "IPv4 format error: Too many octets (>3).");
                return FALSE;
            }

            /* reset for next octet */
            octet=0;
            octetValid=FALSE;
        }
        else
        {
            if(*ipAddr<'0' || *ipAddr>'9')
            {
                strcpy(text_reason, "IPv4 format error: Special character found in IP (Valid: 0-9 and Periods).");
                return FALSE;
            }

            /* convert char to decimal */
            octet *= 10;
            octet += *ipAddr - '0';

            if (octet>255)
            {
                strcpy(text_reason, "IPv4 format error: Octet over 255.");
                return FALSE;
            }

            octetValid=TRUE; /* valid octet */
        }

        ipAddr++; /* move pointer to next character */
    }

    if (cntPrds != 3)
    {
        strcpy(text_reason, "IPv4 format error: Too few octets (<3).");
        return FALSE;
    }

    if (!octetValid) /*redundant*/
    {
        strcpy(text_reason, "IPv4 format error: trailing period.");
        return FALSE;
    }

    return TRUE;
}

/**
 *
 */
void clear(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        /*Do nothing*/
    }
}

/**
 *
 * @return
 */
bool checkExit(void)
{
    char quit[2] = "n";
    bool rc=FALSE;
    memset(quit, '\0', 2);

    printf("\n");
    while(TRUE)
    {
        printf("Terminate Program? (y/n): ");
        scanf("%s", quit);

        if (*quit=='y' || *quit=='n')
        {
            break;
        }
        fflush(stdin);
        memset(quit, '\0', 2);
    }

    if(*quit=='y')
    {
        printf("Program Terminated!\n");
        rc=TRUE;
    }
    fflush(stdin);
    return rc;
}

int main(void)
{
    char text_reason[256] = "Errors!";
    char ipAddr[MAX_IP_LEN] = {'\0'};

    while(TRUE)
    {
        printf("Enter IP to validate: ");
        scanf("%s", ipAddr);

        if(!isIPvalidIPv4Format(ipAddr, text_reason))
        {
            printf("Invalid IP (%s) due to %s\n", ipAddr, text_reason);
        }
        else
        {
            printf("Yes IP is valid (%s)\n", ipAddr);
        }

        if(checkExit())
        {
            break;
        }
    }

    return EXIT_SUCCESS;
}

