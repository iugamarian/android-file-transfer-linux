#ifndef MTPOBJECTSMODEL_H
#define MTPOBJECTSMODEL_H

#include <qabstractitemmodel.h>
#include <mtp/ptp/Device.h>
#include <QVector>

class MtpObjectsModel : public QAbstractListModel
{
	mtp::SessionPtr		_session;
	mtp::u32			_parentObjectId;

	class Row
	{
		std::shared_ptr<mtp::msg::ObjectInfo>	_info;
	public:
		mtp::u32								ObjectId;
		Row(mtp::u32 id = 0): ObjectId(id) { }
		std::shared_ptr<mtp::msg::ObjectInfo> GetInfo(mtp::SessionPtr session);
	};

	mutable QVector<Row>		_rows;

public:
	MtpObjectsModel(QObject *parent = 0);
	~MtpObjectsModel();

	void setSession(mtp::SessionPtr session);
	void setParent(mtp::u32 parentObjectId);

	bool enter(int idx);

	mtp::u32 parentObjectId() const
	{ return _parentObjectId; }

	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // MTPOBJECTSMODEL_H