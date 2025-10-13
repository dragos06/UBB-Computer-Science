namespace WP_Lab10.Models
{
    public class Reservation
    {
        public int Id { get; set; }
        public string Person { get; set; }
        public string Type { get; set; } // "Hotel" or "Flight"
        public int ResourceId { get; set; } // Id of the Hotel or Flight
    }
}
