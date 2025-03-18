#ifndef GOODS_H
#define GOODS_H

#include <string>
#include "SQLAPI/include/SQLAPI.h"

/*
Goods API method declarations
Author(s): 
*/
class Goods {
    public:
        void CreateGoods(SAConnection& con, const std::string& name,
                         const std::string& description, const std::string& SKU,
                         const std::string& category);

        void UpdateGoods(SAConnection& con, const std::string& SKU,
                         const std::string& change_field,
                         const std::string& new_val);

        void SearchGoods(SAConnection& con, const std::string& name);

        void ListAllGoods(SAConnection& con);

        void GetGoodsVolumeByDate(SAConnection& con,
                                  const std::string& start_date,
                                  const std::string& end_date);

        void GetTotalGoodsVolume(SAConnection& con);

        void ListAllGoodsCategories(SAConnection& con);

        void GetGoodsWeightByCategory(SAConnection& con,
                                      const std::string& category);
};
#endif