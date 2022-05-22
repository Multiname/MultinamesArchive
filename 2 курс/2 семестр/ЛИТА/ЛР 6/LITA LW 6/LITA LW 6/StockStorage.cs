using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LITA_LW_6
{
    public class StockStorage
    {
        public void Add(Stock stock) { _stocks.Add(stock); }
        public List<Stock> GetAll() { return _stocks; }
        public List<Stock> GetAllOrdered() { return Stock.Sort(_stocks); }
        public List<Stock> GetAllOrderedByDate() { return Stock.SortByDate(_stocks); }
        public List<Stock> GetAllOrderedByCost() { return Stock.SortByCost(_stocks); }

        public List<Stock> FindByLocation(WarehouseLocation location)
        { return _stocks.FindAll(x => x.Location == location); }
        public List<Stock> FindByZoneAndArea(string zone, string area)
        { return _stocks.FindAll(x => x.Location.Zone == zone && x.Location.Area == area); }
        public List<Stock> FindByNumber(string number)
        { return _stocks.FindAll(x => x.InventoryNumber == number); }

        List<Stock> _stocks = new();
    }
}
