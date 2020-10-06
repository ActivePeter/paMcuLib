extern "C"{
    #include "pa_DataProcessor.h"
    #include "pa_CommonLib/src/drv/pa_CommonDrv/pa_CommonDrv.h"
}
void pa_Convert_Float2Str(float a,char * str,int strlen,char xiaoshuCount){
    int zhengshu=(int)a;
    int zhengshu2=zhengshu;
    float xiaoshu=a-zhengshu;
    int weishu=0;
    if(zhengshu==0)weishu++;
    while (zhengshu>0)
    {
        zhengshu/=10;
        weishu++;
    }
    int weishu2=weishu;
    if(weishu>strlen)
    weishu=strlen;
    while (weishu)
    {
        weishu--;
        str[weishu]=zhengshu2%10+48;
        zhengshu2/=10;
    }
    if(weishu2>=strlen){
        str[strlen-1]='\0';
        return;
    }
    int step=weishu2;
    str[step]='.';
    step++;
    while(step<strlen&&xiaoshuCount>0){
        xiaoshu*=10;
        str[step]=((int)xiaoshu)%10+48;
        step++;
        xiaoshuCount--;
    }
    if(step<strlen){
        str[step]='\0';
    }else{
        str[step-1]='\0';
    }
    
}

