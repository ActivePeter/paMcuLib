extern "C"
{
#include "pa_DataProcessor.h"
#include "pa_CommonLib/src/drv/pa_CommonDrv/pa_CommonDrv.h"
#include "stdarg.h"
}

static const char *const g_pcHex = "0123456789abcdef";

//*****************************************************************************
//
//! Copies a certain number of characters from one string to another.
//!
//! \param s1 is a pointer to the destination buffer into which characters
//! are to be copied.
//! \param s2 is a pointer to the string from which characters are to be
//! copied.
//! \param n is the number of characters to copy to the destination buffer.
//!
//! This function copies at most \e n characters from the string pointed to
//! by \e s2 into the buffer pointed to by \e s1.  If the end of \e s2 is found
//! before \e n characters have been copied, remaining characters in \e s1
//! will be padded with zeroes until \e n characters have been written.  Note
//! that the destination string will only be NULL terminated if the number of
//! characters to be copied is greater than the length of \e s2.
//!
//! \return Returns \e s1.
//
//*****************************************************************************
char *
ustrncpy(char *s1, const char *s2, size_t n)
{
    size_t count;

    //
    // Check the arguments.
    //
    // ASSERT(s1);
    // ASSERT(s2);

    //
    // Start at the beginning of the source string.
    //
    count = 0;

    //
    // Copy the source string until we run out of source characters or
    // destination space.
    //
    while (n && s2[count])
    {
        s1[count] = s2[count];
        count++;
        n--;
    }

    //
    // Pad the destination if we are not yet done.
    //
    while (n)
    {
        s1[count++] = (char)0;
        n--;
    }

    //
    // Pass the destination pointer back to the caller.
    //
    return (s1);
}

//*****************************************************************************
//
//! A simple vsnprintf function supporting \%c, \%d, \%p, \%s, \%u, \%x, and
//! \%X.
//!
//! \param s points to the buffer where the converted string is stored.
//! \param n is the size of the buffer.
//! \param format is the format string.
//! \param arg is the list of optional arguments, which depend on the
//! contents of the format string.
//!
//! This function is very similar to the C library <tt>vsnprintf()</tt>
//! function.  Only the following formatting characters are supported:
//!
//! - \%c to print a character
//! - \%d or \%i to print a decimal value
//! - \%s to print a string
//! - \%u to print an unsigned decimal value
//! - \%x to print a hexadecimal value using lower case letters
//! - \%X to print a hexadecimal value using lower case letters (not upper case
//! letters as would typically be used)
//! - \%p to print a pointer as a hexadecimal value
//! - \%\% to print out a \% character
//!
//! For \%d, \%i, \%p, \%s, \%u, \%x, and \%X, an optional number may reside
//! between the \% and the format character, which specifies the minimum number
//! of characters to use for that value; if preceded by a 0 then the extra
//! characters will be filled with zeros instead of spaces.  For example,
//! ``\%8d'' will use eight characters to print the decimal value with spaces
//! added to reach eight; ``\%08d'' will use eight characters as well but will
//! add zeroes instead of spaces.
//!
//! The type of the arguments after \e format must match the requirements of
//! the format string.  For example, if an integer was passed where a string
//! was expected, an error of some kind will most likely occur.
//!
//! The \e n parameter limits the number of characters that will be
//! stored  in the buffer pointed to by \e s to prevent the possibility of
//! a buffer  overflow.  The buffer size should be large enough to hold the
//! expected converted output string, including the null termination character.
//!
//! The function will return the number of characters that would be converted
//! as if there were no limit on the buffer size.  Therefore it is possible for
//! the function to return a count that is greater than the specified buffer
//! size.  If this happens, it means that the output was truncated.
//!
//! \return Returns the number of characters that were to be stored, not
//! including the NULL termination character, regardless of space in the
//! buffer.
//
//*****************************************************************************
int uvsnprintf(char *s, size_t n, const char *format,
               va_list arg)
{
    unsigned long ulIdx, ulValue, ulCount, ulBase, ulNeg;
    unsigned long ulfloat = 0, ulfloatCnt = 8;

    char *pcStr, cFill;
    int iConvertCount = 0;
    if (n)
    {
        n--;
    }
    iConvertCount = 0;
    while (*format)
    {
        for (ulIdx = 0; (format[ulIdx] != '%') && (format[ulIdx] != '\0');
             ulIdx++)
        {
        }
        if (ulIdx > n)
        {
            ustrncpy(s, format, n);
            s += n;
            n = 0;
        }
        else
        {
            ustrncpy(s, format, ulIdx);
            s += ulIdx;
            n -= ulIdx;
        }
        iConvertCount += ulIdx;
        format += ulIdx;
        if (*format == '%')
        {
            format++;
            ulCount = 0;
            cFill = ' ';
            char hasLimitFCnt = 0;
            int LimitFCnt = 0;
        again:
            char typeChar = *format;
            *format++;
            switch (typeChar) //结束switch进入下一个%
            {
            case '.':
                hasLimitFCnt = 1;
                goto again;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                if (!hasLimitFCnt)
                {
                    if ((format[-1] == '0') && (ulCount == 0))
                    {
                        cFill = '0';
                    }
                    ulCount *= 10;
                    ulCount += format[-1] - '0';
                }else{
                    LimitFCnt *= 10;
                    LimitFCnt += format[-1] - '0';
                }
                goto again;
            }
            case 'c':
            {
                ulValue = va_arg(arg, unsigned long);
                if (n != 0)
                {
                    *s++ = (char)ulValue;
                    n--;
                }
                iConvertCount++;
                break;
            }
            case 'd':
            case 'i':
            {
                ulValue = va_arg(arg, unsigned long);
                if ((long)ulValue < 0)
                {
                    ulValue = -(long)ulValue;
                    ulNeg = 1;
                }
                else
                {
                    ulNeg = 0;
                }
                ulBase = 10;
                goto convert;
            }
            case 's':
            {
                pcStr = va_arg(arg, char *);
                for (ulIdx = 0; pcStr[ulIdx] != '\0'; ulIdx++)
                {
                }
                if (ulCount > ulIdx)
                {
                    iConvertCount += (ulCount - ulIdx);
                }
                if (ulIdx > n)
                {
                    ustrncpy(s, pcStr, n);
                    s += n;
                    n = 0;
                }
                else
                {
                    ustrncpy(s, pcStr, ulIdx);
                    s += ulIdx;
                    n -= ulIdx;
                    if (ulCount > ulIdx)
                    {
                        ulCount -= ulIdx;
                        if (ulCount > n)
                        {
                            ulCount = n;
                        }
                        n = -ulCount;

                        while (ulCount--)
                        {
                            *s++ = ' ';
                        }
                    }
                }
                iConvertCount += ulIdx;
                break;
            }
            case 'u':
            {
                ulValue = va_arg(arg, unsigned long);
                ulBase = 10;
                ulNeg = 0;
                goto convert;
            }
            case 'f':
            {
                ulBase = 10;

                float a;
                a = va_arg(arg, double);

                ulNeg = a < 0;
                if (a < 0)
                {
                    a = -a;
                }
                ulValue = (unsigned long)a;
                a = a - ulValue;
                a *= 10000000;
                int aInt = a;
                ulfloatCnt = 10000000;
                if (aInt == 0)
                {
                    aInt = 0;
                    ulfloatCnt = 10;
                    /* code */
                }
                else
                {
                    /* code */
                    while (aInt % 10 == 0)
                    {

                        aInt /= 10;
                        ulfloatCnt /= 10;
                    }
                }

                ulfloat = aInt;
                if(LimitFCnt){
                    ulfloatCnt=1;
                    while (LimitFCnt)
                    {
                        ulfloatCnt*=10;
                        LimitFCnt--;
                    }
                }
                goto convert;
            }
            case 'x':
            case 'X':
            case 'p':
            {
                ulValue = va_arg(arg, unsigned long);
                ulBase = 16;
                ulNeg = 0;

            convert:
                for (ulIdx = 1;
                     (((ulIdx * ulBase) <= ulValue) &&
                      (((ulIdx * ulBase) / ulBase) == ulIdx));
                     ulIdx *= ulBase, ulCount--)
                {
                }
                if (ulNeg)
                {
                    ulCount--;
                }
                if (ulNeg && (n != 0) && (cFill == '0'))
                {
                    *s++ = '-';
                    n--;
                    iConvertCount++;
                    ulNeg = 0;
                }
                if ((ulCount > 1) && (ulCount < 65536))
                {
                    for (ulCount--; ulCount; ulCount--)
                    {
                        if (n != 0)
                        {
                            *s++ = cFill;
                            n--;
                        }
                        iConvertCount++;
                    }
                }

                
                if (ulNeg && (n != 0))
                {
                   
                    *s++ = '-';
                    n--;

                    
                    iConvertCount++;
                }

                
                for (; ulIdx; ulIdx /= ulBase)
                {
                    if (n != 0)
                    {
                        *s++ = g_pcHex[(ulValue / ulIdx) % ulBase];
                        n--;
                    }

                    iConvertCount++;
                }
                if (ulfloatCnt > 0)
                {
                    if (n != 0)
                    {
                        *s++ = '.';
                        n--;
                        iConvertCount++;
                    }
                    ulfloatCnt /= 10;
                    for (; ulfloatCnt; ulfloatCnt /= 10)
                    {
                        if (n != 0)
                        {
                            *s++ = g_pcHex[(ulfloat / ulfloatCnt) % 10];
                            n--;
                            iConvertCount++;
                        }
                    }
                }
                break;
            }
            case '%':
            {
                if (n != 0)
                {
                    *s++ = format[-1];
                    n--;
                }
                iConvertCount++;
                break;
            }
            default:
            {
                if (n >= 5)
                {
                    ustrncpy(s, "ERROR", 5);
                    s += 5;
                    n -= 5;
                }
                else
                {
                    ustrncpy(s, "ERROR", n);
                    s += n;
                    n = 0;
                }
                iConvertCount += 5;
                break;
            }
            }
        }
    }
    *s = 0;
    return (iConvertCount);
}
//重写的低资源消耗的的snprintf
int pa_snprintf(char *s, int n, const char *format, ...)
{
    va_list arg;
    int ret;

    va_start(arg, format);
    ret = uvsnprintf(s, n, format, arg);

    va_end(arg);
    return (ret);
}