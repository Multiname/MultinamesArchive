using Microsoft.VisualStudio.TestTools.UnitTesting;
using LITA_LW_6;
using System;
using System.Collections.Generic;

namespace Testing
{
    [TestClass]
    public class Testing
    {
        [TestMethod]
        public void TestDefaultComparison()
        {
            WarehouseLocation location = new WarehouseLocation("A", "a", 1);
            Stock stock_1 = new Stock(1, "1", DateTimeOffset.Parse("01.01.2001"), 100, location);
            Stock stock_2 = new Stock(2, "2", DateTimeOffset.Parse("02.02.2002"), 200, location);

            Assert.AreEqual(true, stock_1 < stock_2);
            Assert.AreEqual(false, stock_1 > stock_2);
            Assert.AreEqual(true, stock_1 <= stock_2);
            Assert.AreEqual(false, stock_1 >= stock_2);
            Assert.AreEqual(false, stock_1 == stock_2);
            Assert.AreEqual(true, stock_1 != stock_2);
        }

        [TestMethod]
        public void TestSorting()
        {
            WarehouseLocation location = new WarehouseLocation("A", "a", 1);
            Stock stock_1 = new Stock(1, "1", DateTimeOffset.Parse("01.01.2001"), 100, location);
            Stock stock_2 = new Stock(2, "2", DateTimeOffset.Parse("02.02.2002"), 200, location);
            Stock stock_3 = new Stock(3, "3", DateTimeOffset.Parse("03.03.2003"), 300, location);
            List<Stock> list = new List<Stock>();
            list.Add(stock_3);
            list.Add(stock_1);
            list.Add(stock_2);

            List<Stock> sorted = Stock.Sort(list);
            Assert.AreEqual((uint)1, sorted[0].Id);
            Assert.AreEqual((uint)2, sorted[1].Id);
            Assert.AreEqual((uint)3, sorted[2].Id);
        }
    }
}
