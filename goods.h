#ifndef GOODS_H
#define GOODS_H

#include <string>

//Update this to include SKU and Category
class Goods {
    public:
        void CreateGoods(std::string name, std::string description);

        void UpdateGoods(std::string name, std::string description,
                         std::string update_field);

        void SearchGoods(std::string name);

        void ListAllGoods();

        void GetGoodsVolumeByDate(std::string start_date, std::string end_date);

        void GetTotalGoodsVolume();
};
#endif