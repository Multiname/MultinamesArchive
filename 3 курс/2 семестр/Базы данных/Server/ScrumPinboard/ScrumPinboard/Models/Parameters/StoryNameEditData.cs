namespace ScrumPinboard.Models.Parameters
{
    public class StoryNameEditData
    {
        public int StoryId { get; set; }
        public string Name { get; set; }

        public StoryNameEditData(int storyId, string name)
        {
            StoryId = storyId;
            Name = name;
        }
    }
}
