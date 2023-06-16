namespace ScrumPinboard.Models.Parameters
{
    public class StoryStateEditData
    {
        public int storyId { get; set; }
        public SprintStory.ProcessState state { get; set; }

        public StoryStateEditData(int storyId, SprintStory.ProcessState state)
        {
            this.storyId = storyId;
            this.state = state;
        }
    }
}
