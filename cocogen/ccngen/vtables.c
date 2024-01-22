#include "ccngen/actions.h"
#include "ccn/ccn_types.h"
#include "ccn/dynamic_core.h"
const ccn_trav_ft print_vtable[_NT_SIZE] = { &TRAVerror, &PRTid, &PRTienum, &PRTvisit_sequence_visit, &PRTvisit_sequence_eval, &PRTvisit, &PRTvisit_arg_list, &PRTattribute_reference, &PRTequation_dependency, &PRTequation, &PRTattribute, &PRTitravdata, &PRTsetoperation, &PRTsetliteral, &PRTsetreference, &PRTste, &PRTchild, &PRTlifetime_range, &PRTilifetime, &PRTnodeset_child_entry, &PRTinodeset, &PRTinode, &PRTipass, &PRTitraversal, &PRTiphase, &PRTiactions, &PRTast, };
const ccn_trav_ft setliteralcontains_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &SLCsetliteral, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVchildren, };
const ccn_trav_ft setliteraldifference_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &SLDsetliteral, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVchildren, };
const ccn_trav_ft setliteralintersect_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &SLISsetliteral, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVchildren, };
const ccn_trav_ft setliteralunion_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &SLUsetliteral, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVchildren, };
const ccn_trav_ft setliteralinsert_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &SLIsetliteral, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVchildren, };
const ccn_trav_ft scheduleattributevisits_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &SAVast, };
const ccn_trav_ft reachability_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &RCBsetliteral, &TRAVnop, &TRAVnop, &RCBchild, &TRAVnop, &TRAVnop, &TRAVnop, &RCBinodeset, &RCBinode, &TRAVnop, &RCBitraversal, &TRAVnop, &TRAVnop, &RCBast, };
const ccn_trav_ft checkproductrules_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &CPRequation_dependency, &CPRequation, &CPRattribute, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &CPRchild, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &CPRinode, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &CPRast, };
const ccn_trav_ft checkattributes_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &CHAattribute, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &CHAinodeset, &CHAinode, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVchildren, };
const ccn_trav_ft propagateattributes_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &PRAsetliteral, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &PRAnodeset_child_entry, &PRAinodeset, &TRAVchildren, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &PRAast, };
const ccn_trav_ft unwrapsetexpr_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &USEsetoperation, &USEsetliteral, &USEsetreference, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &USEast, };
const ccn_trav_ft nodesetchildtable_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &NCTsetoperation, &NCTsetliteral, &NCTsetreference, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &NCTinodeset, &TRAVchildren, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &NCTast, };
const ccn_trav_ft buildsymboltable_vtable[_NT_SIZE] = { &TRAVerror, &BSTid, &BSTienum, &BSTvisit_sequence_visit, &BSTvisit_sequence_eval, &BSTvisit, &BSTvisit_arg_list, &BSTattribute_reference, &BSTequation_dependency, &BSTequation, &BSTattribute, &BSTitravdata, &BSTsetoperation, &BSTsetliteral, &BSTsetreference, &BSTste, &BSTchild, &BSTlifetime_range, &BSTilifetime, &BSTnodeset_child_entry, &BSTinodeset, &BSTinode, &BSTipass, &BSTitraversal, &BSTiphase, &BSTiactions, &BSTast, };
const ccn_trav_ft checkexistance_vtable[_NT_SIZE] = { &TRAVerror, &CEXid, &CEXienum, &CEXvisit_sequence_visit, &CEXvisit_sequence_eval, &CEXvisit, &CEXvisit_arg_list, &CEXattribute_reference, &CEXequation_dependency, &CEXequation, &CEXattribute, &CEXitravdata, &CEXsetoperation, &CEXsetliteral, &CEXsetreference, &CEXste, &CEXchild, &CEXlifetime_range, &CEXilifetime, &CEXnodeset_child_entry, &CEXinodeset, &CEXinode, &CEXipass, &CEXitraversal, &CEXiphase, &CEXiactions, &CEXast, };
const ccn_trav_ft dynamicgenvisitsource_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &DGVSvisit_sequence_visit, &DGVSvisit_sequence_eval, &DGVSvisit, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &DGVSast, };
const ccn_trav_ft dynamicgenvisitfunctions_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &DGVFvisit, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &DGVFast, };
const ccn_trav_ft dynamicgennodemacros_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &DGNMattribute, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &DGNMchild, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &DGNMinode, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &DGNMast, };
const ccn_trav_ft dynamicgennodestructs_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &DGNSattribute, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &DGNSchild, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &DGNSinode, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &DGNSast, };
const ccn_trav_ft dynamicgennodeinitfunctions_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &DGIFattribute, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &DGIFchild, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &DGIFinode, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &DGIFast, };
const ccn_trav_ft dynamicgennodeunion_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &DGBUinode, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &DGBUast, };
const ccn_trav_ft dynamicgennodeconstructor_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &DGNCattribute, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &DGNCchild, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &DGNCinode, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &DGNCast, };
const ccn_trav_ft dynamicgenenum_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &DGEinodeset, &DGEinode, &DGEipass, &DGEitraversal, &TRAVnop, &TRAVnop, &DGEast, };
const ccn_trav_ft dynamicgenenumvalues_vtable[_NT_SIZE] = { &TRAVerror, &DGEVid, &DGEVienum, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &DGEVast, };
const ccn_trav_ft dynamicgentravvtable_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &DGTVitraversal, &TRAVnop, &TRAVnop, &DGTVast, };
const ccn_trav_ft dynamicgennodesfortravtable_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &DGNFTTinode, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &DGNFTTast, };
const ccn_trav_ft dynamicgenpasstable_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &DGPTipass, &TRAVchildren, &TRAVnop, &TRAVnop, &DGPTast, };
const ccn_trav_ft dynamicgentravtable_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &DGTTitraversal, &TRAVnop, &TRAVnop, &DGTTast, };
const ccn_trav_ft dynamicgensystemtraversals_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &DGSTinode, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &DGSTast, };
const ccn_trav_ft dynamicgenactionsheader_vtable[_NT_SIZE] = { &TRAVerror, &DGAHid, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &DGAHsetliteral, &TRAVchildren, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVchildren, &DGAHinode, &DGAHipass, &DGAHitraversal, &TRAVchildren, &TRAVchildren, &DGAHast, };
const ccn_trav_ft dynamicgentravactions_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &DGTAinode, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &DGTAast, };
const ccn_trav_ft dynamicgencopytraversal_vtable[_NT_SIZE] = { &TRAVerror, &DGCTid, &DGCTienum, &DGCTvisit_sequence_visit, &DGCTvisit_sequence_eval, &DGCTvisit, &DGCTvisit_arg_list, &DGCTattribute_reference, &DGCTequation_dependency, &DGCTequation, &DGCTattribute, &DGCTitravdata, &DGCTsetoperation, &DGCTsetliteral, &DGCTsetreference, &DGCTste, &DGCTchild, &DGCTlifetime_range, &DGCTilifetime, &DGCTnodeset_child_entry, &DGCTinodeset, &DGCTinode, &DGCTipass, &DGCTitraversal, &DGCTiphase, &DGCTiactions, &DGCTast, };
const ccn_trav_ft dynamicgenconstructorcall_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &DGCCattribute, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &DGCCchild, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &DGCCinode, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &DGCCast, };
const ccn_trav_ft dynamicgenfreetraversal_vtable[_NT_SIZE] = { &TRAVerror, &DGFTid, &DGFTienum, &DGFTvisit_sequence_visit, &DGFTvisit_sequence_eval, &DGFTvisit, &DGFTvisit_arg_list, &DGFTattribute_reference, &DGFTequation_dependency, &DGFTequation, &DGFTattribute, &DGFTitravdata, &DGFTsetoperation, &DGFTsetliteral, &DGFTsetreference, &DGFTste, &DGFTchild, &DGFTlifetime_range, &DGFTilifetime, &DGFTnodeset_child_entry, &DGFTinodeset, &DGFTinode, &DGFTipass, &DGFTitraversal, &DGFTiphase, &DGFTiactions, &DGFTast, };
const ccn_trav_ft dynamicgenchecktraversal_vtable[_NT_SIZE] = { &TRAVerror, &DGCHTid, &DGCHTienum, &DGCHTvisit_sequence_visit, &DGCHTvisit_sequence_eval, &DGCHTvisit, &DGCHTvisit_arg_list, &DGCHTattribute_reference, &DGCHTequation_dependency, &DGCHTequation, &DGCHTattribute, &DGCHTitravdata, &DGCHTsetoperation, &DGCHTsetliteral, &DGCHTsetreference, &DGCHTste, &DGCHTchild, &DGCHTlifetime_range, &DGCHTilifetime, &DGCHTnodeset_child_entry, &DGCHTinodeset, &DGCHTinode, &DGCHTipass, &DGCHTitraversal, &DGCHTiphase, &DGCHTiactions, &DGCHTast, };
const ccn_trav_ft dynamicgentravdatastructs_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &DGTDSitravdata, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &DGTDSitraversal, &TRAVnop, &TRAVnop, &DGTDSast, };
const ccn_trav_ft dynamicgentravdatactors_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &DGTDCitravdata, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &DGTDCitraversal, &TRAVnop, &TRAVnop, &TRAVchildren, };
const ccn_trav_ft dynamicgentravdatactorsheader_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &DGTDCHitraversal, &TRAVnop, &TRAVnop, &TRAVchildren, };
const ccn_trav_ft dynamicgentravdatagetters_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &DGTDGitraversal, &TRAVnop, &TRAVnop, &TRAVchildren, };
const ccn_trav_ft dynamicgentravdataunion_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &DGTDUitraversal, &TRAVnop, &TRAVnop, &DGTDUast, };
const ccn_trav_ft dynamicgentravfunctions_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &DGT_Fchild, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &DGT_Finode, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &DGT_Fast, };
const ccn_trav_ft genactionarray_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &GAAipass, &GAAitraversal, &GAAiphase, &TRAVnop, &GAAast, };
const ccn_trav_ft genactionarrayheader_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &GAAHipass, &GAAHitraversal, &GAAHiphase, &TRAVnop, &GAAHast, };
const ccn_trav_ft genidstables_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVchildren, &GITiphase, &GITiactions, &GITast, };
const ccn_trav_ft gengateheader_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVchildren, &GGHiphase, &TRAVnop, &GGHast, };
const ccn_trav_ft dynamicgentravdatatables_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &DGTDTitraversal, &TRAVnop, &TRAVnop, &DGTDTast, };
const ccn_trav_ft gendot_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &GDattribute, &TRAVnop, &TRAVchildren, &GDsetliteral, &TRAVnop, &TRAVnop, &GDchild, &TRAVnop, &TRAVnop, &TRAVnop, &GDinodeset, &GDinode, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &GDast, };
const ccn_trav_ft dynamicusergentraversals_vtable[_NT_SIZE] = { &TRAVerror, &DUGTid, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVchildren, &DUGTinode, &TRAVchildren, &DUGTitraversal, &TRAVchildren, &TRAVchildren, &DUGTast, };
const ccn_trav_ft dynamicusergenpasses_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &DUGPipass, &TRAVchildren, &TRAVnop, &TRAVnop, &DUGPast, };
const ccn_trav_ft staticgennodestructs_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &SGNSattribute, &TRAVnop, &TRAVchildren, &SGNSsetliteral, &TRAVnop, &TRAVnop, &SGNSchild, &TRAVnop, &TRAVnop, &TRAVnop, &SGNSinodeset, &SGNSinode, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &SGNSast, };
const ccn_trav_ft mapidtolifetime_vtable[_NT_SIZE] = { &TRAVerror, &MITLid, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVchildren, &MITLlifetime_range, &MITLilifetime, &TRAVnop, &TRAVchildren, &MITLinode, &TRAVchildren, &TRAVchildren, &TRAVchildren, &MITLiactions, &MITLast, };
const ccn_trav_ft assignidtoaction_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVchildren, &TRAVchildren, &AITAiactions, &AITAast, };
const ccn_trav_ft checklifetimes_vtable[_NT_SIZE] = { &TRAVerror, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &CLTattribute, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVnop, &TRAVchildren, &TRAVchildren, &TRAVnop, &TRAVchildren, &TRAVnop, &TRAVnop, &CLTast, };
const ccn_pass_ft ccn_pass_vtable[_PASS_SIZE] = { &PASSerror, &dynamicSwitchToVisitSource, &dynamic_start_visit_header, &dynamicGenBaseNodeInit, &dynamicSwitchToAstSource, &dynamicGenBaseNode, &dynamic_start_ast_header, &dynamicSwitchTravData, &dynamicStartTravData, &dynamicStartTableGen, &dynamicStartEnumHeader, &doOpts, &genDefines, &SPscanAndParse, };
const ccn_trav_ft ccn_copy_vtable[_NT_SIZE] = { &TRAVerror, &CPYid, &CPYienum, &CPYvisit_sequence_visit, &CPYvisit_sequence_eval, &CPYvisit, &CPYvisit_arg_list, &CPYattribute_reference, &CPYequation_dependency, &CPYequation, &CPYattribute, &CPYitravdata, &CPYsetoperation, &CPYsetliteral, &CPYsetreference, &CPYste, &CPYchild, &CPYlifetime_range, &CPYilifetime, &CPYnodeset_child_entry, &CPYinodeset, &CPYinode, &CPYipass, &CPYitraversal, &CPYiphase, &CPYiactions, &CPYast, };
const ccn_trav_ft ccn_check_vtable[_NT_SIZE] = { &TRAVerror, &CHKid, &CHKienum, &CHKvisit_sequence_visit, &CHKvisit_sequence_eval, &CHKvisit, &CHKvisit_arg_list, &CHKattribute_reference, &CHKequation_dependency, &CHKequation, &CHKattribute, &CHKitravdata, &CHKsetoperation, &CHKsetliteral, &CHKsetreference, &CHKste, &CHKchild, &CHKlifetime_range, &CHKilifetime, &CHKnodeset_child_entry, &CHKinodeset, &CHKinode, &CHKipass, &CHKitraversal, &CHKiphase, &CHKiactions, &CHKast, };
const ccn_trav_ft ccn_free_vtable[_NT_SIZE] = { &TRAVerror, &DELid, &DELienum, &DELvisit_sequence_visit, &DELvisit_sequence_eval, &DELvisit, &DELvisit_arg_list, &DELattribute_reference, &DELequation_dependency, &DELequation, &DELattribute, &DELitravdata, &DELsetoperation, &DELsetliteral, &DELsetreference, &DELste, &DELchild, &DELlifetime_range, &DELilifetime, &DELnodeset_child_entry, &DELinodeset, &DELinode, &DELipass, &DELitraversal, &DELiphase, &DELiactions, &DELast, };
const ccn_trav_ft ccn_error_vtable[_NT_SIZE] = { &TRAVerror, &TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,&TRAVerror,};
const ccn_trav_ft *ccn_trav_vtable[_TRAV_SIZE] = { ccn_error_vtable, print_vtable, setliteralcontains_vtable, setliteraldifference_vtable, setliteralintersect_vtable, setliteralunion_vtable, setliteralinsert_vtable, scheduleattributevisits_vtable, reachability_vtable, checkproductrules_vtable, checkattributes_vtable, propagateattributes_vtable, unwrapsetexpr_vtable, nodesetchildtable_vtable, buildsymboltable_vtable, checkexistance_vtable, dynamicgenvisitsource_vtable, dynamicgenvisitfunctions_vtable, dynamicgennodemacros_vtable, dynamicgennodestructs_vtable, dynamicgennodeinitfunctions_vtable, dynamicgennodeunion_vtable, dynamicgennodeconstructor_vtable, dynamicgenenum_vtable, dynamicgenenumvalues_vtable, dynamicgentravvtable_vtable, dynamicgennodesfortravtable_vtable, dynamicgenpasstable_vtable, dynamicgentravtable_vtable, dynamicgensystemtraversals_vtable, dynamicgenactionsheader_vtable, dynamicgentravactions_vtable, dynamicgencopytraversal_vtable, dynamicgenconstructorcall_vtable, dynamicgenfreetraversal_vtable, dynamicgenchecktraversal_vtable, dynamicgentravdatastructs_vtable, dynamicgentravdatactors_vtable, dynamicgentravdatactorsheader_vtable, dynamicgentravdatagetters_vtable, dynamicgentravdataunion_vtable, dynamicgentravfunctions_vtable, genactionarray_vtable, genactionarrayheader_vtable, genidstables_vtable, gengateheader_vtable, dynamicgentravdatatables_vtable, gendot_vtable, dynamicusergentraversals_vtable, dynamicusergenpasses_vtable, staticgennodestructs_vtable, mapidtolifetime_vtable, assignidtoaction_vtable, checklifetimes_vtable, ccn_free_vtable, ccn_check_vtable, ccn_copy_vtable, };
const ccn_trav_data_ft trav_data_init_vtable[_TRAV_SIZE] = {TRAVdataNOP,TRAVdataNOP,TRAVdataInitsetliteralContains,TRAVdataInitsetliteralDifference,TRAVdataInitsetliteralIntersect,TRAVdataInitsetliteralUnion,TRAVdataInitsetliteralInsert,TRAVdataInitscheduleAttributeVisits,TRAVdataNOP,TRAVdataInitcheckProductRules,TRAVdataInitcheckAttributes,TRAVdataInitpropagateAttributes,TRAVdataNOP,TRAVdataInitnodesetChildTable,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataInitdynamicGenCheckTraversal,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataInitdynamicGenTravFunctions,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataInitdynamicGenTravDataTables,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP, TRAVdataNOP, TRAVdataNOP};
const ccn_trav_data_ft trav_data_free_vtable[_TRAV_SIZE] = {TRAVdataNOP,TRAVdataNOP,TRAVdataFreesetliteralContains,TRAVdataFreesetliteralDifference,TRAVdataFreesetliteralIntersect,TRAVdataFreesetliteralUnion,TRAVdataFreesetliteralInsert,TRAVdataFreescheduleAttributeVisits,TRAVdataNOP,TRAVdataFreecheckProductRules,TRAVdataFreecheckAttributes,TRAVdataFreepropagateAttributes,TRAVdataNOP,TRAVdataFreenodesetChildTable,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataFreedynamicGenCheckTraversal,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataFreedynamicGenTravFunctions,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataFreedynamicGenTravDataTables,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP,TRAVdataNOP, TRAVdataNOP, TRAVdataNOP};
