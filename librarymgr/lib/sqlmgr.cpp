#include "sqlmgr.h"
#include <QCoreApplication>

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDateTime>

SqlMgr* SqlMgr::instance = nullptr;

SqlMgr::SqlMgr() {}

SqlMgr::~SqlMgr()
{

}

void SqlMgr::init()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");

    m_db.setDatabaseName(QCoreApplication::applicationDirPath()+"/db/book.db");

    qDebug()<<m_db.open();
}

bool SqlMgr::login(QString strUser, QString strPass,int &Userid)
{
    QSqlQuery q(m_db);
    QString strSql = QString("select * from user where username = '%1' and password = '%2'").arg(strUser).arg(strPass);
    bool ret = q.exec(strSql);
    if(!ret){
        qDebug()<<q.lastError().text();
    }else{
        ret = q.next();
        if(ret){
            Userid = q.value(0).toInt();
        }

    }
    return ret;
}

int SqlMgr::signup(QString strUser,QString strPass,QString grade,QString department,QString name)
{
    QSqlQuery q(m_db);
    int re = 1;
    QString strSql = QString("select * from user where username = '%1'").arg(strUser);
    bool ret = q.exec(strSql);
    if(!ret){
        qDebug()<<q.lastError().text();
    }else{
        ret = q.next();
        if(ret == 1){
            re = 2;
        }else{
            strSql = QString("insert into user VALUES(NULL,'%1','%2','%3','%4','%5','%6','%7');")
            .arg(100)
                .arg(grade)
                .arg(department)
                .arg("SO")
                .arg(name)
                .arg(strPass)
                .arg(strUser);
            bool cnt = q.exec(strSql);
            if(!cnt){
                re = 0;
                qDebug()<<q.lastError().text();
            }
        }
    }

    return re;
}

QVector<QStringList> SqlMgr::getUsers(QString strCondition)
{      //"select * from user username like '%%1%'"
    QSqlQuery q(m_db);
    QString strSql = QString("select * from user %1").arg(strCondition);
    QVector<QStringList> vec;
    bool ret = q.exec(strSql);
    if(!ret){
        qDebug()<<q.lastError().text();
    }
    else{
        int iCols = q.record().count();
        QStringList l;
        while(q.next()){
            l.clear();
            for(int i = 0;i < iCols;i++){
                l << q.value(i).toString();
            }
            vec.push_back(l);
        }
    }
    return vec;
}

void SqlMgr::AddUser(QVector<QStringList> v)
{
    m_db.transaction();
    QSqlQuery q(m_db);
    for(auto it:v){
        QString strSql = QString("insert into user VALUES(NULL,'%1','%2','%3','%4','%5','%6','%7');")
                             .arg(it[0])
                             .arg(it[1])
                             .arg(it[2])
                             .arg(it[3])
                             .arg(it[4])
                             .arg(it[5])
                             .arg(it[6]);
        bool ret = q.exec(strSql);
        if(!ret){

            qDebug()<<q.lastError().text();
        }
    }


    m_db.commit();
}

void SqlMgr::delUser(QString strId)
{
    QSqlQuery q(m_db);
    QString strSql = QString("delete from user where userid = '%1'").arg(strId);
    bool ret = q.exec(strSql);
    if(!ret){
        qDebug()<<q.lastError().text();
    }

}

QVector<QStringList> SqlMgr::getBooks(QString strCondition)
{
    QSqlQuery q(m_db);
    QString strSql = QString("select * from book %1").arg(strCondition);
    QVector<QStringList> vec;
    bool ret = q.exec(strSql);
    if(!ret){
        qDebug()<<q.lastError().text();
    }
    else{
        int iCols = q.record().count();
        QStringList l;
        while(q.next()){
            l.clear();
            for(int i = 0;i < iCols;i++){
                l << q.value(i).toString();
            }
            vec.push_back(l);
        }
    }
    return vec;
}

void SqlMgr::AddBooks(QVector<QStringList> vec)
{
    if(0 == vec.size()){
        return;
    }
    auto ldata = vec[0];
    QSqlQuery q(m_db);
    QString strSql = QString("INSERT INTO book "
                             "values(null,'%1','%2','%3','%4','%5',%6,'')"
                             ).arg(ldata[1],ldata[2],ldata[3],ldata[4],ldata[5],ldata[6]);
    bool ret = q.exec(strSql);
    if(!ret){
        qDebug()<<q.lastError().text();
    }

}

void SqlMgr::UpdateBooks(QStringList ldata)
{
    QSqlQuery q(m_db);
    QString strSql = QString("UPDATE book "
                             "set name = '%1',press = '%2',type1 = '%3',type2 = '%4',type3 = '%5',cnt = '%6'"
                             " where bookid = %7").arg(ldata[1],ldata[2],ldata[3],ldata[4],ldata[5],ldata[6],ldata[0]);
    bool ret = q.exec(strSql);
    if(!ret){
        qDebug()<<q.lastError().text();
    }

}

QString SqlMgr::delBook(QString strId)
{
    QString strRet;
    QSqlQuery q(m_db);
    QString strSql = QString("delete from book where bookid = '%1'").arg(strId);
    bool ret = q.exec(strSql);
    if(!ret){
        qDebug()<<q.lastError().text();
        strRet = "删除失败，请检查";
    }
    return strRet;
}

// QString SqlMgr::returnbook(QString strUserId, QString strBookId)
// {
//     //实现图书接口
//     QSqlQuery q(m_db);
//     QString strSql = QString("update book set cnt = cnt + 1 where bookid = %1").arg(strBookId);



//     bool ret = q.exec(strSql);
//     if(!ret){
//         qDebug()<<q.lastError().text();
//     }

//     strSql = QString("delete from record where bookid = %2 and userid = %1").arg(strUserId).arg(strBookId);
//     ret = q.exec(strSql);
//     if(!ret){
//         qDebug()<<q.lastError().text();
//     }
//     return QString("");
// }
QString SqlMgr::returnbook(QString strUserId, QString strBookId)
{
    QSqlQuery q(m_db);

    // 更新书籍库存
    QString strSql = QString("UPDATE book SET cnt = cnt + 1 WHERE bookid = %1").arg(strBookId);
    bool ret = q.exec(strSql);
    if (!ret) {
        qDebug() << q.lastError().text();
        return "更新书籍库存失败";
    }

    // 查询应还时间
    strSql = QString("SELECT end FROM record WHERE userid = '%1' AND bookid = '%2'")
                 .arg(strUserId).arg(strBookId);
    ret = q.exec(strSql);
    if (!ret || !q.next()) {
        qDebug() << "未找到借阅记录：" << q.lastError().text();
        return "未找到借阅记录";
    }

    QString returnTimeStr = q.value(0).toString();
    QDateTime returnTime = QDateTime::fromString(returnTimeStr, "yyyy-MM-dd HH:mm:ss");
    QDateTime now = QDateTime::currentDateTime();

    qint64 secondsOverdue = now.toSecsSinceEpoch() - returnTime.toSecsSinceEpoch();
    int daysOverdue = qMax(0, static_cast<int>(secondsOverdue / (3600 * 24)));

    // 构造返回信息
    QString result;
    if (daysOverdue > 0) {
        double penalty = daysOverdue * 5.0;
        result = QString("您超时了%1天，需要交%2元的罚款")
                     .arg(daysOverdue)
                     .arg(penalty, 0, 'f', 2);  // 保留两位小数
        strSql = QString("UPDATE user SET credit = credit - 1 WHERE userid = %1").arg(strUserId);
        ret = q.exec(strSql);
        if (!ret) {
            qDebug() << q.lastError().text();
            return "修改信誉积分失败";
        }
    } else {
        result = "还书成功，未超时";
    }

    // 删除借阅记录
    strSql = QString("DELETE FROM record WHERE userid = '%1' AND bookid = '%2'")
                 .arg(strUserId).arg(strBookId);
    ret = q.exec(strSql);
    if (!ret) {
        qDebug() << "删除借阅记录失败：" << q.lastError().text();
        return "删除借阅记录失败";
    }

    return result;
}

QString SqlMgr::borrowbook(QString strUserId, QString strBookId)
{
    QSqlQuery q(m_db);

    // 更新书籍库存
    QString strSql = QString("UPDATE book SET cnt = cnt - 1 WHERE bookid = %1").arg(strBookId);
    bool ret = q.exec(strSql);
    if (!ret) {
        qDebug() << q.lastError().text();
        return "更新书籍库存失败";
    }

    // 获取用户权限信息
    QSqlQuery userQuery(m_db);
    userQuery.prepare("SELECT auth FROM user WHERE userid = :userid");
    userQuery.bindValue(":userid", strUserId);
    if (!userQuery.exec()) {
        qDebug() << userQuery.lastError().text();
        return "查询用户权限失败";
    }

    int borrowDays = 10; // 默认普通用户10天
    if (userQuery.next()) {
        QString auth = userQuery.value(0).toString();
        if (!auth.isEmpty() && auth.endsWith('V')) {
            borrowDays = 15; // VIP用户15天
        }
    }

    // 获取当前时间戳及未来时间戳
    qint64 now = QDateTime::currentSecsSinceEpoch();
    qint64 future = now + 3600 * 24 * borrowDays;

    // 格式化为可读字符串
    QString nowStr = QDateTime::fromSecsSinceEpoch(now).toString("yyyy-MM-dd HH:mm:ss");
    QString futureStr = QDateTime::fromSecsSinceEpoch(future).toString("yyyy-MM-dd HH:mm:ss");

    // 构建插入语句，注意使用单引号包裹字符串
    strSql = QString("INSERT INTO record VALUES (null, %1, %2, '%3', '%4')")
                 .arg(strUserId)
                 .arg(strBookId)
                 .arg(nowStr)
                 .arg(futureStr);

    ret = q.exec(strSql);
    if (!ret) {
        qDebug() << q.lastError().text();
        return "记录借阅信息失败";
    }

    return QString("");
}

QVector<QStringList> SqlMgr::getRecord(QString strCondition)
{
    QSqlQuery q(m_db);
    QString strSql = QString("select * from record join user using(userid) join book using(bookid) %1").arg(strCondition);
    QVector<QStringList> vec;
    bool ret = q.exec(strSql);
    if(!ret){
        qDebug()<<q.lastError().text();
    }
    else{
        int iCols = q.record().count();
        QStringList l;
        while(q.next()){
            l.clear();
            for(int i = 0;i < iCols;i++){
                l << q.value(i).toString();
            }
            vec.push_back(l);
        }
    }
    return vec;
}

void SqlMgr::clearRecord()
{
    QSqlQuery q(m_db);
    QString strSql = QString("DELETE from record");
    bool ret = q.exec(strSql);
    if(!ret){
        qDebug()<<q.lastError().text();
    }
    strSql = QString("DELETE FROM sqlite_sequence WHERE name = 'record'");
    ret = q.exec(strSql);
    if(!ret){
        qDebug()<<q.lastError().text();
    }

}

