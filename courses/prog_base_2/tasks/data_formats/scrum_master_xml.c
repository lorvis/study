#include "scrum_master_xml.h"
struct teammate
{
    char * name;
    char * surname;
    char * skill;
};

struct scrum_master
{
    char * name;
    char * surname;
    char * birthdate;
    char * skill;
    float height;
    int course;
    int teamsize;
    teammate_t * team;
};

struct scrum_masters
{
    int sm_amount;
    scrum_master_t * scrumlist;
};

static char * _xmlGetContentByChildName(xmlNode * xInput,const char * name){

    char * res = "";
    for(xmlNode * xI = xInput->children; NULL != xI; xI = xI->next)
    {
        if ((XML_ELEMENT_NODE == xI->type)&&(strcmp(xI->name,name)==0))
        {
            res = xmlNodeGetContent(xI);
            return res;
        }
    }

return NULL;
}

static char * _xmlGetChildByName(xmlNode * xInput,const char * name){

    for(xmlNode * xI = xInput->children; NULL != xI; xI = xI->next)
    {
        if ((XML_ELEMENT_NODE == xI->type)&&(strcmp(xI->name,name)==0))
        {
            return xI;
        }
    }

return NULL;
}

 scrum_masters_t * xml_sm_new(const char * xmlfilename)
{
    int smcount=0,tmmcount=0;
    char line[100];
    char text[20480] = "";
    FILE * fr = fopen(xmlfilename,"r");

    while(fgets(line,100,fr))
    {
        strcat(text,line);
    }

    xmlDoc * xDoc;

    xDoc = xmlReadMemory(text,strlen(text),NULL, NULL, 0);

    if (NULL == xDoc)
    {
        printf("Error parsing xml from memory");
        fclose(fr);
        return 1;
    }

    fclose(fr);

    xmlNode * xRootEl;

    xRootEl = xmlDocGetRootElement(xDoc);

    scrum_masters_t * to_fill = malloc(sizeof(scrum_masters_t));
    to_fill->scrumlist = malloc(sizeof(scrum_master_t));
    to_fill->sm_amount = 0;

    for(xmlNode * xCur = xRootEl->children; NULL != xCur; xCur = xCur->next)
    {

        if (XML_ELEMENT_NODE == xCur->type)
        {
            to_fill->sm_amount++;

            realloc(to_fill->scrumlist,to_fill->sm_amount*sizeof(scrum_master_t));

            to_fill->scrumlist[to_fill->sm_amount-1].name = _xmlGetContentByChildName(xCur,"Name");
            to_fill->scrumlist[to_fill->sm_amount-1].surname = _xmlGetContentByChildName(xCur,"Surname");
            to_fill->scrumlist[to_fill->sm_amount-1].birthdate = _xmlGetContentByChildName(xCur,"Birthdate");
            to_fill->scrumlist[to_fill->sm_amount-1].skill = _xmlGetContentByChildName(xCur,"Skill");
            to_fill->scrumlist[to_fill->sm_amount-1].height = atof(_xmlGetContentByChildName(xCur,"Height"));
            to_fill->scrumlist[to_fill->sm_amount-1].course = atoi(_xmlGetContentByChildName(xCur,"Course"));

                       xmlNode * xJ = _xmlGetChildByName(xCur,"Team");

                        to_fill->scrumlist[to_fill->sm_amount-1].teamsize = 0;

                        for(xmlNode * xK = xJ->children; NULL != xK; xK = xK->next)
                        {
                            if (XML_ELEMENT_NODE == xK->type)
                            {
                                to_fill->scrumlist[to_fill->sm_amount-1].teamsize++;

                                if(to_fill->scrumlist[to_fill->sm_amount-1].teamsize!=1)
                                    realloc(to_fill->scrumlist[to_fill->sm_amount-1].team,sizeof(teammate_t)*to_fill->scrumlist[to_fill->sm_amount-1].teamsize);
                                else
                                    to_fill->scrumlist[to_fill->sm_amount-1].team = malloc(sizeof(teammate_t));
                                to_fill->scrumlist[to_fill->sm_amount-1].team[to_fill->scrumlist[to_fill->sm_amount-1].teamsize-1].name = xmlGetProp(xK,"Name");
                                to_fill->scrumlist[to_fill->sm_amount-1].team[to_fill->scrumlist[to_fill->sm_amount-1].teamsize-1].surname = _xmlGetContentByChildName(xK,"Surname");
                                to_fill->scrumlist[to_fill->sm_amount-1].team[to_fill->scrumlist[to_fill->sm_amount-1].teamsize-1].skill = _xmlGetContentByChildName(xK,"Skill");
                            }
                        }

        }
    }
    return to_fill;
}

    void xm_sm_printOut(scrum_masters_t * to_print){

    for(int i = 0;i<to_print->sm_amount;i++){

    printf("Scrum master %i:\n",i+1);
    printf("\t Name : %s\n",to_print->scrumlist[i].name);
    printf("\t Surname : %s\n",to_print->scrumlist[i].surname);
    printf("\t Birthdate : %s\n",to_print->scrumlist[i].birthdate);
    printf("\t Skill : %s\n",to_print->scrumlist[i].skill);
    printf("\t Height : %f\n",to_print->scrumlist[i].height);
    printf("\t Course : %i\n",to_print->scrumlist[i].course);
    puts("\t Team:\n\n");

    for(int j = 0;j<to_print->scrumlist[i].teamsize;j++){

    printf("\t\tTeammate %i:\n",j);
    printf("\t\t\t Name : %s\n",to_print->scrumlist[i].team[j].name);
    printf("\t\t\t Surname : %s\n",to_print->scrumlist[i].team[j].surname);
    printf("\t\t\t Skill : %s\n\n",to_print->scrumlist[i].team[j].skill);

    }

    }

    }


    void xm_sm_free(scrum_masters_t * to_free){
    for(int i = 0;i<to_free->sm_amount;i++){
    free(to_free->scrumlist[i].team);
    }
    free(to_free->scrumlist);
    free(to_free);
    }
