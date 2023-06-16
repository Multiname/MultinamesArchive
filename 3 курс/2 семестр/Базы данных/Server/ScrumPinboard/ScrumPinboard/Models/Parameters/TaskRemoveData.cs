namespace ScrumPinboard.Models.Parameters
{
    public class TaskRemoveData
    {
        public int TaskId { get; set; }

        public TaskRemoveData(int taskId)
        {
            TaskId = taskId;
        }
    }
}
