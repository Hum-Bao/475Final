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
        static void CreateGoods(SAConnection& con, const std::string& name,
                                const std::string& description,
                                const std::string& SKU,
                                const std::string& category);

        static void UpdateGoods(SAConnection& con, const std::string& SKU,
                                const std::string& change_field,
                                std::string new_val);

        static void SearchGoods(SAConnection& con, const std::string& name);

        static void ListAllGoods(SAConnection& con);

        static void GetGoodsVolumeByDate(SAConnection& con,
                                         const std::string& start_date,
                                         const std::string& end_date);

        static void GetTotalGoodsVolume(SAConnection& con);

        static void CreateGoodsCategory(SAConnection& con,
                                        const std::string& name);

        static void ListAllGoodsCategories(SAConnection& con);

        static void GetGoodsWeightByCategory(SAConnection& con,
                                             const std::string& category);
};
#endif