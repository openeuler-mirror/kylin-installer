/*
 *    rpm installer
 *    Copyright (c) KylinSoft  Co., Ltd. 2023. All rights reserved.
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
#ifndef DATASTRUCTDEFINES_H
#define DATASTRUCTDEFINES_H

#include <QObject>
#include <QString>
//定义公用的数据结构
//data struct defines

#ifdef Q_OS_LINUX
#define KYRPM_RPMPATH "/usr/bin/rpm"
#define RPM_NVS " -q --qf=\"%{name}\n%{version}-%{release}\n%{summary}\n\" "
#define RPM_DESCRIPTION   " -q --qf=%{description} "
#else
//#define KYRPM_RPMPATH "brew"
#define KYRPM_RPMPATH "/usr/local/Cellar/rpm/4.17.0_1/bin/rpm"
#endif

#define KYRPM_YUMPATH "/usr/bin/yum"
#define KYRPM_RPMBUILD	"rpm"
#define TESTRPM "/Users/douyan/temp/kyrpm-installer/NetworkManager-1.32.12-14.oe2203sp1.src.rpm"
#define VERSION "1.0-1"

enum Architecuture {
    x86_64 = 0,
    aarch,
    unknown
};

//typedef struct				/**** Distribution Structure ****/
//{
//  char		product[256],		/* Product name */
//        version[256],		/* Product version string */
//        release[256],		/* Product release string */
//        copyright[256],		/* Product copyright */
//        vendor[256],		/* Vendor name */
//        packager[256],		/* Packager name */
//        license[256],		/* License file to copy */
//        readme[256];		/* README file to copy */
//  int		num_subpackages;	/* Number of subpackages */
//  char		**subpackages;		/* Subpackage names */
//  int		num_descriptions;	/* Number of description strings */
//  description_t	*descriptions;		/* Description strings */
//  int		vernumber,		/* Version number */
//        epoch;			/* Epoch number */
//  int		num_commands;		/* Number of commands */
//  command_t	*commands;		/* Commands */
//  int		num_depends;		/* Number of dependencies */
//  depend_t	*depends;		/* Dependencies */
//  int		num_files;		/* Number of files */
//  file_t	*files;			/* Files */
//} dist_t;


//todo:need define in QObject:class
//Q_ENUM(Architecuture);

//class Architecuture: public QObject
//{
//    Q_OBJECT
//public:
//    Architecuture() {}
//    virtual ~Architecuture() {}
//};

//rpm info
struct RPMInfo
{
    QString packageName;
    QString epoch;
    QString version;
    QString release;
    Architecuture arch;
    QString installDate;
    QString group;
    int size;
    QString licenses;
    QString signature;
    QString source;
    QString buildDate;
    QString buildHost;
    QString url;
    QString summary;
    QString description;

    void clear() {
        packageName="";
        epoch="";
        version="";
        release="";
        arch=unknown;
        installDate="";
        group="";
        size=-1;
        licenses="";
        signature="";
        source="";
        buildDate="";
        buildHost="";
        url="";
        summary="";
        description="";
    }
};

#endif // DATASTRUCTDEFINES_H
