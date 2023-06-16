namespace ScrumPinboard.Models.Parameters
{
    public class SprintNameEditData
    {
        public int Id { get; set; }
        public string Name { get; set; }

        public SprintNameEditData(int id, string name)
        {
            Id = id;
            Name = name;
        }
    }
}
