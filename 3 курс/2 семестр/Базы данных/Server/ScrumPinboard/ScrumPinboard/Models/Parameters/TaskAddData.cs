namespace ScrumPinboard.Models.Parameters
{
    public class TaskAddData
    {
        public string Name { get; set; }
        public int StoryId { get; set; }
        public int EstimatedHours { get; set; }

        public TaskAddData(string name, int storyId, int estimatedHours)
        {
            Name = name;
            StoryId = storyId;
            EstimatedHours = estimatedHours;
        }
    }
}
