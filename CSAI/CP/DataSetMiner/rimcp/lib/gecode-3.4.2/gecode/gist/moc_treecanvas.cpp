/****************************************************************************
** Meta object code from reading C++ file 'treecanvas.hh'
**
** Created: Tue Mar 22 19:52:06 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gecode/gist/treecanvas.hh"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'treecanvas.hh' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Gecode__Gist__SearcherThread[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      41,   30,   29,   29, 0x05,
      61,   29,   29,   29, 0x05,
      81,   29,   29,   29, 0x05,
      99,   29,   29,   29, 0x05,
     122,   29,   29,   29, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_Gecode__Gist__SearcherThread[] = {
    "Gecode::Gist::SearcherThread\0\0w,h,scale0\0"
    "update(int,int,int)\0statusChanged(bool)\0"
    "scaleChanged(int)\0solution(const Space*)\0"
    "searchFinished()\0"
};

const QMetaObject Gecode::Gist::SearcherThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Gecode__Gist__SearcherThread,
      qt_meta_data_Gecode__Gist__SearcherThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Gecode::Gist::SearcherThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Gecode::Gist::SearcherThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Gecode::Gist::SearcherThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Gecode__Gist__SearcherThread))
        return static_cast<void*>(const_cast< SearcherThread*>(this));
    return QThread::qt_metacast(_clname);
}

int Gecode::Gist::SearcherThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: update((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: statusChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: scaleChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: solution((*reinterpret_cast< const Space*(*)>(_a[1]))); break;
        case 4: searchFinished(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Gecode::Gist::SearcherThread::update(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Gecode::Gist::SearcherThread::statusChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Gecode::Gist::SearcherThread::scaleChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Gecode::Gist::SearcherThread::solution(const Space * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Gecode::Gist::SearcherThread::searchFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
static const uint qt_meta_data_Gecode__Gist__TreeCanvas[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      63,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   25,   25,   25, 0x05,
      44,   25,   25,   25, 0x05,
      66,   25,   25,   25, 0x05,
     101,   98,   25,   25, 0x05,
     144,   25,   25,   25, 0x05,
     167,   25,   25,   25, 0x05,
     187,  184,   25,   25, 0x05,
     214,  210,   25,   25, 0x05,

 // slots: signature, parameters, type, tag, flags
     254,  235,   25,   25, 0x0a,
     290,  277,   25,   25, 0x2a,
     316,  309,   25,   25, 0x2a,
     331,   25,   25,   25, 0x0a,
     343,   25,   25,   25, 0x0a,
     355,   25,   25,   25, 0x0a,
     370,   25,   25,   25, 0x0a,
     383,   25,   25,   25, 0x0a,
     395,   25,   25,   25, 0x0a,
     408,   25,   25,   25, 0x0a,
     420,   25,   25,   25, 0x0a,
     432,   25,   25,   25, 0x0a,
     453,   25,   25,   25, 0x0a,
     461,   25,   25,   25, 0x0a,
     473,   25,   25,   25, 0x0a,
     509,  493,   25,   25, 0x0a,
     542,  538,   25,   25, 0x2a,
     567,   25,   25,   25, 0x2a,
     588,   25,   25,   25, 0x0a,
     606,   25,   25,   25, 0x0a,
     619,   25,   25,   25, 0x0a,
     627,   25,   25,   25, 0x0a,
     635,   25,   25,   25, 0x0a,
     645,   25,   25,   25, 0x0a,
     655,   25,   25,   25, 0x0a,
     666,   25,   25,   25, 0x0a,
     681,  676,   25,   25, 0x0a,
     698,   25,   25,   25, 0x2a,
     711,   25,   25,   25, 0x0a,
     724,   25,   25,   25, 0x0a,
     739,   25,   25,   25, 0x0a,
     749,   25,   25,   25, 0x0a,
     763,   25,   25,   25, 0x0a,
     783,   25,   25,   25, 0x0a,
     811,   25,   25,   25, 0x0a,
     839,  831,   25,   25, 0x0a,
     869,  867,   25,   25, 0x0a,
     893,  867,   25,   25, 0x0a,
     916,   25,  911,   25, 0x0a,
     936,   25,  911,   25, 0x0a,
     950,  867,   25,   25, 0x0a,
     970,   25,  911,   25, 0x0a,
     988,  986,   25,   25, 0x0a,
    1004,  986,   25,   25, 0x0a,
    1025,   25,  911,   25, 0x0a,
    1050,  867,   25,   25, 0x0a,
    1079,   25,   25,   25, 0x0a,
    1095,   25,  911,   25, 0x0a,
    1104,   25,   25,   25, 0x0a,
    1113,   25,   25,   25, 0x0a,
    1133, 1122,   25,   25, 0x0a,
    1157,   25,   25,   25, 0x08,
    1179, 1177,   25,   25, 0x08,
    1208, 1206,   25,   25, 0x08,
    1238,  986,   25,   25, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Gecode__Gist__TreeCanvas[] = {
    "Gecode::Gist::TreeCanvas\0\0scaleChanged(int)\0"
    "autoZoomChanged(bool)\0"
    "contextMenu(QContextMenuEvent*)\0,,\0"
    "statusChanged(VisualNode*,Statistics,bool)\0"
    "solution(const Space*)\0searchFinished()\0"
    "id\0addedBookmark(QString)\0idx\0"
    "removedBookmark(int)\0scale0,zoomx,zoomy\0"
    "scaleTree(int,int,int)\0scale0,zoomx\0"
    "scaleTree(int,int)\0scale0\0scaleTree(int)\0"
    "searchAll()\0searchOne()\0toggleHidden()\0"
    "hideFailed()\0unhideAll()\0toggleStop()\0"
    "unstopAll()\0exportPDF()\0exportWholeTreePDF()\0"
    "print()\0zoomToFit()\0centerCurrentNode()\0"
    "fix,inspectorNo\0inspectCurrentNode(bool,int)\0"
    "fix\0inspectCurrentNode(bool)\0"
    "inspectCurrentNode()\0inspectBeforeFP()\0"
    "stopSearch()\0reset()\0navUp()\0navDown()\0"
    "navLeft()\0navRight()\0navRoot()\0back\0"
    "navNextSol(bool)\0navNextSol()\0"
    "navPrevSol()\0bookmarkNode()\0setPath()\0"
    "inspectPath()\0startCompareNodes()\0"
    "startCompareNodesBeforeFP()\0"
    "emitStatusChanged()\0c_d,a_d\0"
    "setRecompDistances(int,int)\0b\0"
    "setAutoHideFailed(bool)\0setAutoZoom(bool)\0"
    "bool\0getAutoHideFailed()\0getAutoZoom()\0"
    "setShowCopies(bool)\0getShowCopies()\0"
    "i\0setRefresh(int)\0setRefreshPause(int)\0"
    "getSmoothScrollAndZoom()\0"
    "setSmoothScrollAndZoom(bool)\0"
    "resizeToOuter()\0finish()\0update()\0"
    "scroll()\0w,h,scale0\0layoutDone(int,int,int)\0"
    "statusChanged(bool)\0n\0exportNodePDF(VisualNode*)\0"
    "s\0inspectSolution(const Space*)\0"
    "scroll(int)\0"
};

const QMetaObject Gecode::Gist::TreeCanvas::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Gecode__Gist__TreeCanvas,
      qt_meta_data_Gecode__Gist__TreeCanvas, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Gecode::Gist::TreeCanvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Gecode::Gist::TreeCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Gecode::Gist::TreeCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Gecode__Gist__TreeCanvas))
        return static_cast<void*>(const_cast< TreeCanvas*>(this));
    return QWidget::qt_metacast(_clname);
}

int Gecode::Gist::TreeCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: scaleChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: autoZoomChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: contextMenu((*reinterpret_cast< QContextMenuEvent*(*)>(_a[1]))); break;
        case 3: statusChanged((*reinterpret_cast< VisualNode*(*)>(_a[1])),(*reinterpret_cast< const Statistics(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 4: solution((*reinterpret_cast< const Space*(*)>(_a[1]))); break;
        case 5: searchFinished(); break;
        case 6: addedBookmark((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: removedBookmark((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: scaleTree((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 9: scaleTree((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: scaleTree((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: searchAll(); break;
        case 12: searchOne(); break;
        case 13: toggleHidden(); break;
        case 14: hideFailed(); break;
        case 15: unhideAll(); break;
        case 16: toggleStop(); break;
        case 17: unstopAll(); break;
        case 18: exportPDF(); break;
        case 19: exportWholeTreePDF(); break;
        case 20: print(); break;
        case 21: zoomToFit(); break;
        case 22: centerCurrentNode(); break;
        case 23: inspectCurrentNode((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 24: inspectCurrentNode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: inspectCurrentNode(); break;
        case 26: inspectBeforeFP(); break;
        case 27: stopSearch(); break;
        case 28: reset(); break;
        case 29: navUp(); break;
        case 30: navDown(); break;
        case 31: navLeft(); break;
        case 32: navRight(); break;
        case 33: navRoot(); break;
        case 34: navNextSol((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: navNextSol(); break;
        case 36: navPrevSol(); break;
        case 37: bookmarkNode(); break;
        case 38: setPath(); break;
        case 39: inspectPath(); break;
        case 40: startCompareNodes(); break;
        case 41: startCompareNodesBeforeFP(); break;
        case 42: emitStatusChanged(); break;
        case 43: setRecompDistances((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 44: setAutoHideFailed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 45: setAutoZoom((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 46: { bool _r = getAutoHideFailed();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 47: { bool _r = getAutoZoom();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 48: setShowCopies((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 49: { bool _r = getShowCopies();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 50: setRefresh((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 51: setRefreshPause((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: { bool _r = getSmoothScrollAndZoom();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 53: setSmoothScrollAndZoom((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 54: resizeToOuter(); break;
        case 55: { bool _r = finish();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 56: update(); break;
        case 57: scroll(); break;
        case 58: layoutDone((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 59: statusChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 60: exportNodePDF((*reinterpret_cast< VisualNode*(*)>(_a[1]))); break;
        case 61: inspectSolution((*reinterpret_cast< const Space*(*)>(_a[1]))); break;
        case 62: scroll((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 63;
    }
    return _id;
}

// SIGNAL 0
void Gecode::Gist::TreeCanvas::scaleChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Gecode::Gist::TreeCanvas::autoZoomChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Gecode::Gist::TreeCanvas::contextMenu(QContextMenuEvent * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Gecode::Gist::TreeCanvas::statusChanged(VisualNode * _t1, const Statistics & _t2, bool _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Gecode::Gist::TreeCanvas::solution(const Space * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Gecode::Gist::TreeCanvas::searchFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void Gecode::Gist::TreeCanvas::addedBookmark(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Gecode::Gist::TreeCanvas::removedBookmark(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
