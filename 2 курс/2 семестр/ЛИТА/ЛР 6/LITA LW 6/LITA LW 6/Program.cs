using System;
using System.Collections.Generic;

namespace LITA_LW_6
{
    class Program
    {
        static void Main(string[] args)
        {
            WarehouseLocation locationA = new("A", "a", 1);
            WarehouseLocation locationB = new("B", "b", 2);
            WarehouseLocation locationC = new("B", "b", 3);
            StockStorage storage = new();
            storage.Add(new(1, "1", DateTimeOffset.Parse("01.01.2001"), 300, locationA));
            storage.Add(new(8, "8", DateTimeOffset.Parse("02.02.2002"), 700, locationC));
            storage.Add(new(5, "5", DateTimeOffset.Parse("03.03.2003"), 500, locationB));
            storage.Add(new(4, "1", DateTimeOffset.Parse("04.04.2004"), 100, locationA));
            storage.Add(new(6, "6", DateTimeOffset.Parse("01.01.2001"), 400, locationC));
            storage.Add(new(3, "1", DateTimeOffset.Parse("02.02.2002"), 800, locationA));
            storage.Add(new(2, "2", DateTimeOffset.Parse("03.03.2003"), 200, locationB));
            storage.Add(new(7, "7", DateTimeOffset.Parse("04.04.2004"), 600, locationB));

            string command = "";

            while (command != "0")
            {
                Console.Clear();

                foreach (var stock in storage.GetAll())
                    Console.WriteLine("ID: {0}; Inventory number: {1}; Arrival date: {2}; Cost: {3}; Zone: {4}; Area: {5}; Cell: {6}",
                            stock.Id, stock.InventoryNumber, stock.ArrivalDate.DateTime.ToShortDateString(), stock.Cost,
                            stock.Location.Zone, stock.Location.Area, stock.Location.Cell);

                Console.WriteLine("\n1. Get all ordered");
                Console.WriteLine("2. Get all ordered by date");
                Console.WriteLine("3. Get all ordered by cost");
                Console.WriteLine("4. Find by location");
                Console.WriteLine("5. Find by zone and area");
                Console.WriteLine("6. Find by number");
                Console.WriteLine("7. Add");
                Console.WriteLine("0. Exit");
                Console.Write(">>> ");
                command = Console.ReadLine();
                Console.WriteLine();

                if (command == "1")
                {
                    foreach (var stock in storage.GetAllOrdered())
                        Console.WriteLine("ID: {0}; Inventory number: {1}; Arrival date: {2}; Cost: {3}; Zone: {4}; Area: {5}; Cell: {6}",
                            stock.Id, stock.InventoryNumber, stock.ArrivalDate.DateTime.ToShortDateString(), stock.Cost,
                            stock.Location.Zone, stock.Location.Area, stock.Location.Cell);
                    Console.ReadKey();
                }
                else if (command == "2")
                {
                    foreach (var stock in storage.GetAllOrderedByDate())
                        Console.WriteLine("ID: {0}; Inventory number: {1}; Arrival date: {2}; Cost: {3}; Zone: {4}; Area: {5}; Cell: {6}",
                            stock.Id, stock.InventoryNumber, stock.ArrivalDate.DateTime.ToShortDateString(), stock.Cost,
                            stock.Location.Zone, stock.Location.Area, stock.Location.Cell);
                    Console.ReadKey();
                }
                else if (command == "3")
                {
                    foreach (var stock in storage.GetAllOrderedByCost())
                        Console.WriteLine("ID: {0}; Inventory number: {1}; Arrival date: {2}; Cost: {3}; Zone: {4}; Area: {5}; Cell: {6}",
                            stock.Id, stock.InventoryNumber, stock.ArrivalDate.DateTime.ToShortDateString(), stock.Cost,
                            stock.Location.Zone, stock.Location.Area, stock.Location.Cell);
                    Console.ReadKey();
                }
                else if (command == "4")
                {
                    string zone;
                    string area;
                    uint cell;

                    Console.Write("Zone: ");
                    zone = Console.ReadLine();
                    Console.Write("Area: ");
                    area = Console.ReadLine();
                    Console.Write("Cell: ");
                    cell = uint.Parse(Console.ReadLine());
                    Console.WriteLine();

                    foreach (var stock in storage.FindByLocation(new(zone, area, cell)))
                        Console.WriteLine("ID: {0}; Inventory number: {1}; Arrival date: {2}; Cost: {3}; Zone: {4}; Area: {5}; Cell: {6}",
                            stock.Id, stock.InventoryNumber, stock.ArrivalDate.DateTime.ToShortDateString(), stock.Cost,
                            stock.Location.Zone, stock.Location.Area, stock.Location.Cell);
                    Console.ReadKey();
                }
                else if (command == "5")
                {
                    string zone;
                    string area;

                    Console.Write("Zone: ");
                    zone = Console.ReadLine();
                    Console.Write("Area: ");
                    area = Console.ReadLine();
                    Console.WriteLine();

                    foreach (var stock in storage.FindByZoneAndArea(zone, area))
                        Console.WriteLine("ID: {0}; Inventory number: {1}; Arrival date: {2}; Cost: {3}; Zone: {4}; Area: {5}; Cell: {6}",
                            stock.Id, stock.InventoryNumber, stock.ArrivalDate.DateTime.ToShortDateString(), stock.Cost,
                            stock.Location.Zone, stock.Location.Area, stock.Location.Cell);
                    Console.ReadKey();
                }
                else if (command == "6")
                {
                    string number;

                    Console.Write("Inventory number: ");
                    number = Console.ReadLine();
                    Console.WriteLine();

                    foreach (var stock in storage.FindByNumber(number))
                        Console.WriteLine("ID: {0}; Inventory number: {1}; Arrival date: {2}; Cost: {3}; Zone: {4}; Area: {5}; Cell: {6}",
                            stock.Id, stock.InventoryNumber, stock.ArrivalDate.DateTime.ToShortDateString(), stock.Cost,
                            stock.Location.Zone, stock.Location.Area, stock.Location.Cell);
                    Console.ReadKey();
                }
                else if (command == "7")
                {
                    uint id;
                    string inventoryNumber;
                    string arrivalDate;
                    uint cost;
                    string zone;
                    string area;
                    uint cell;

                    Console.Write("ID: ");
                    id = uint.Parse(Console.ReadLine());
                    Console.Write("Inventory number: ");
                    inventoryNumber = Console.ReadLine();
                    Console.Write("Arrival date: ");
                    arrivalDate = Console.ReadLine();
                    Console.Write("Cost: ");
                    cost = uint.Parse(Console.ReadLine());

                    Console.Write("Zone: ");
                    zone = Console.ReadLine();
                    Console.Write("Area: ");
                    area = Console.ReadLine();
                    Console.Write("Cell: ");
                    cell = uint.Parse(Console.ReadLine());
                    Console.WriteLine();

                    storage.Add(new(id, inventoryNumber, DateTimeOffset.Parse(arrivalDate), cost, new(zone, area, cell)));
                }
            }
        }
    }
}
