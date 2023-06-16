namespace ScrumPinboard.Models.Parameters
{
    public class StoryDeveloperEditData
    {
        public int StoryId { get; set; }
        public int DeveloperId { get; set; }

        public StoryDeveloperEditData(int storyId, int developerId)
        {
            StoryId = storyId;
            DeveloperId = developerId;
        }
    }
}
