namespace ScrumPinboard.Models.Parameters
{
    public class SprintRemoveData
    {
        public int sprintId { get; set; }

        public SprintRemoveData(int sprintId)
        {
            this.sprintId = sprintId;
        }
    }
}
