namespace ScrumPinboard.Models.Parameters
{
    public class StoryRemoveData
    {
        public int StoryId { get; set; }

        public StoryRemoveData(int storyId)
        {
            StoryId = storyId;
        }
    }
}
