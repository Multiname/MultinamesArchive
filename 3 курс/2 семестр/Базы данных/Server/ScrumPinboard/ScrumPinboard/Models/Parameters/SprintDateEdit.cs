namespace ScrumPinboard.Models.Parameters
{
    public class SprintDateEdit
    {
        public int Id { get; set; }
        public string Date { get; set; }
        public bool isStart { get; set; }

        public SprintDateEdit(int id, string date, bool isStart)
        {
            Id = id;
            Date = date;
            this.isStart = isStart;
        }
    }
}
