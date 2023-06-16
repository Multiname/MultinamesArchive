namespace ScrumPinboard.Models.Parameters
{
    public class EpicNameEditData
    {
        public int EpicId { get; set; }
        public string Name { get; set; }

        public EpicNameEditData(int epicId, string name)
        {
            EpicId = epicId;
            Name = name;
        }
    }
}
