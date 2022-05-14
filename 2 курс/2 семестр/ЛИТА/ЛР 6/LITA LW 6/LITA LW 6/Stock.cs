using System;
using System.Collections.Generic;

namespace LITA_LW_6
{
    public class Stock 
    {
        public Stock(uint id, string inventoryNumber, DateTimeOffset arrivalDate, uint cost, WarehouseLocation location)
        {
            Id = id;
            InventoryNumber = inventoryNumber;
            ArrivalDate = arrivalDate;
            Cost = cost;
            Location = location;
        }

        public uint Id { get; }
        public string InventoryNumber { get; set; }
        public DateTimeOffset ArrivalDate { get; set; }
        public uint Cost { get; set; }
        public WarehouseLocation Location { get; set; }

        public static bool operator <(Stock first, Stock second) => first.Id < second.Id;
        public static bool operator >(Stock first, Stock second) => first.Id > second.Id;
        public static bool operator <=(Stock first, Stock second) => first.Id <= second.Id;
        public static bool operator >=(Stock first, Stock second) => first.Id >= second.Id;
        public static bool operator ==(Stock first, Stock second) => first.Id == second.Id;
        public static bool operator !=(Stock first, Stock second) => first.Id != second.Id;

        public static List<Stock> Sort(List<Stock> list)
        {
            int i = 0;
            bool isUnsorted = true;
            while (isUnsorted)
            {
                isUnsorted = false;
                for (int j = 0; j < list.Count - i - 1; ++j)
                    if (list[j] > list[j + 1])
                    {
                        Stock temp = list[j];
                        list[j] = list[j + 1];
                        list[j + 1] = temp;
                        isUnsorted = true;
                    }
                ++i;
            }

            return list;
        }

        public static List<Stock> SortByDate(List<Stock> list)
        {
            int i = 0;
            bool isUnsorted = true;
            while (isUnsorted)
            {
                isUnsorted = false;
                for (int j = 0; j < list.Count - i - 1; ++j)
                {
                    if (list[j].ArrivalDate < list[j + 1].ArrivalDate)
                    {
                        Stock temp = list[j];
                        list[j] = list[j + 1];
                        list[j + 1] = temp;
                        isUnsorted = true;
                    }
                    else if (list[j].ArrivalDate == list[j + 1].ArrivalDate)
                    {
                        bool isNeededToSort = false;
                        for (int k = 0; k < (list[j].InventoryNumber.Length > list[j + 1].InventoryNumber.Length ? 
                            list[j + 1].InventoryNumber.Length : list[j].InventoryNumber.Length); ++k )
                        {
                            if (list[j].InventoryNumber[k] > list[j].InventoryNumber[k])
                            {
                                isNeededToSort = true;
                                break;
                            }
                            if (list[j].InventoryNumber[k] < list[j].InventoryNumber[k])
                            {
                                break;
                            }
                        }

                        if (isNeededToSort)
                        {
                            Stock temp = list[j];
                            list[j] = list[j + 1];
                            list[j + 1] = temp;
                            isUnsorted = true;
                        }
                    }
                }
                ++i;
            }

            return list;
        }
    }
}
