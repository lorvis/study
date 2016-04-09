#include "scrum_master_xml.h"

int main() {
scrum_master_t * new_sm = xml_sm_new("scrum_master.xml");
xm_sm_printOut(new_sm);
xm_sm_free(new_sm);
return 0;
}
