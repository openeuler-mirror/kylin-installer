#include "DataStructDefines.h"

const QString RPMInfo::rpminfo_key_Qstring[] = {
        "Name", "Epoch", "Version", "Release", "Arch", "Install Data", "Group", "Size",
        "License", "Signature", "Source RPM", "Build Data", "Build Host", "Packager",
        "URL", "Summary", "Description", ""
};

void RPMInfo::clear(){
    info.clear();
}

QString RPMInfo::getInfo(RPMINFO_KEY key){
    auto rtn = info.find(key);
    if(rtn == info.end()){
        return "";
    }
    return rtn.value();
}

bool RPMInfo::setInfo(RPMINFO_KEY key, const QString &value){
    info[key] = value;
    return true;
}

bool RPMInfo::setInfo(const QString &key, const QString &value){
    for(int i=0;i<int(RPMINFO_KEY::__count);++i){
        if(rpminfo_key_Qstring[i] == key){
            info[RPMINFO_KEY(i)] = value;
            return true;
        }
    }
    return false;
}
