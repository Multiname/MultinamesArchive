namespace ScrumPinboard.Models.Parameters
{
    public class StoryIsPickedEditData
    {
        public bool IsPicked { get; set; }
        public int SprintId { get; set; }
        public int StoryId { get; set; }

        public StoryIsPickedEditData(bool isPicked, int sprintId, int storyId)
        {
            IsPicked = isPicked;
            SprintId = sprintId;
            StoryId = storyId;
        }
    }
}
