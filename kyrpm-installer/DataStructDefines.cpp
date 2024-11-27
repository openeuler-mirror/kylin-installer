/*
 *    rpm installer
 *    Copyright (c) KylinSoft  Co., Ltd. 2024. All rights reserved.
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, version 2.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */
#include "DataStructDefines.h"
#include <QDebug>

const QString RPMInfo::rpminfo_key_Qstring[] = {
        "Name", "Epoch", "Version", "Release", "Architecture", "Install Date", "Group", "Size",
        "License", "Signature", "Source RPM", "Build Date", "Build Host", "Packager",
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
