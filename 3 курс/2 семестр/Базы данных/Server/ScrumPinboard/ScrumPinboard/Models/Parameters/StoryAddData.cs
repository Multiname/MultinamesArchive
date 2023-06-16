namespace ScrumPinboard.Models.Parameters
{
    public class StoryAddData
    {
        public string Name { get; set; }
        public int EpicId { get; set; }
        public int StoryPoints { get; set; }

        public StoryAddData(string name, int epicId, int storyPoints)
        {
            Name = name;
            EpicId = epicId;
            StoryPoints = storyPoints;
        }
    }
}
