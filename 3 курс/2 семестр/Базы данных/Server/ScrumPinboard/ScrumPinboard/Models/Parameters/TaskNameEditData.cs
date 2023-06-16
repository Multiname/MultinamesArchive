namespace ScrumPinboard.Models.Parameters
{
    public class TaskNameEditData
    {
        public int TaskId { get; set; }
        public string Name { get; set; }

        public TaskNameEditData(int taskId, string name)
        {
            TaskId = taskId;
            Name = name;
        }
    }
}
