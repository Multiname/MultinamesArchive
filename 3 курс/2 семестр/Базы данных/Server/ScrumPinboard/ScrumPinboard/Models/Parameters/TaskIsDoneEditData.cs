namespace ScrumPinboard.Models.Parameters
{
    public class TaskIsDoneEditData
    {
        public int TaskId { get; set; }
        public bool IsDone { get; set; }

        public TaskIsDoneEditData(int taskId, bool isDone)
        {
            TaskId = taskId;
            IsDone = isDone;
        }
    }
}
