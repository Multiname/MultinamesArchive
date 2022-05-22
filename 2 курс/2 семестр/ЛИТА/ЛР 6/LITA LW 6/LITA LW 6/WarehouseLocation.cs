namespace LITA_LW_6
{
    public class WarehouseLocation
    {
        public WarehouseLocation(string zone, string area, uint cell)
        {
            Zone = zone;
            Area = area;
            Cell = cell;
        }

        public string Zone { get; set; }
        public string Area { get; set; }
        public uint Cell { get; set; }

        public static bool operator ==(WarehouseLocation first, WarehouseLocation second) =>
            first.Zone == second.Zone && first.Area == second.Area && first.Cell == second.Cell;
        public static bool operator !=(WarehouseLocation first, WarehouseLocation second) => !(first == second);
    }
}
