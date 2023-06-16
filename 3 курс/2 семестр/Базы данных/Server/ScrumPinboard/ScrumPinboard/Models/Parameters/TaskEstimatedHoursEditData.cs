namespace ScrumPinboard.Models.Parameters
{
    public class TaskEstimatedHoursEditData
    {
        public int TaskId { get; set; }
        public int EstimatedHours { get; set; }

        public TaskEstimatedHoursEditData(int taskId, int estimatedHours)
        {
            TaskId = taskId;
            EstimatedHours = estimatedHours;
        }
    }
}
