#include "goods.h"

void Goods::CreateGoods(SAConnection& con, const std::string& name,
                        const std::string& description, const std::string& SKU,
                        const std::string& category) {}

void Goods::UpdateGoods(SAConnection& con, const std::string& SKU,
                        const std::string& change_field,
                        const std::string& new_val) {}

void Goods::SearchGoods(SAConnection& con, const std::string& name) {}

void Goods::ListAllGoods(SAConnection& con) {}

void Goods::GetGoodsVolumeByDate(SAConnection& con,
                                 const std::string& start_date,
                                 const std::string& end_date) {}

void Goods::GetTotalGoodsVolume(SAConnection& con) {}

void Goods::CreateGoodsCategory(SAConnection& con, const std::string& name) {}

void Goods::ListAllGoodsCategories(SAConnection& con) {}

void Goods::GetGoodsWeightByCategory(SAConnection& con,
                                     const std::string& category) {}