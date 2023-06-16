namespace ScrumPinboard.Models.Parameters
{
    public class StoryPointsEditData
    {
        public int StoryId { get; set; }
        public int StoryPoints { get; set; }

        public StoryPointsEditData(int storyId, int storyPoints)
        {
            StoryId = storyId;
            StoryPoints = storyPoints;
        }
    }
}
