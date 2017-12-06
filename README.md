# konvector

QVariant BDData::headerData(int section, Qt::Orientation orientation, int role) const //???
{
    if (role == Qt::DisplayRole){
        if (orientation == Qt::Horizontal) {
            return column_name[section];  // "Time";
            // else return "Difference";
        }
    }
    return  QAbstractTableModel::headerData(section, orientation, role);
}


 emit beginInsertColumns(QModelIndex(), 0, columns.count()-1);
добавить такое, говорит об изменении данных в модели
    emit endInsertColumns();
    
    убрать лоад ту вью, сделать по другому, по классике
