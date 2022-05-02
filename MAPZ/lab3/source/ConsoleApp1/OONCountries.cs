using System;
using System.Linq;
using System.Collections.Generic;

namespace ConsoleApp1
{
    public class WorldRegion
    {
        public string Name{ get; set; }
        public int Id{ get; set; }
    }
    public static class OONCountryExtension
    {
        public static string GetWorldRegionName(this OONCountry oonCountry, List<WorldRegion> worldRegions)
        {
            return worldRegions.Where(x => x.Id == oonCountry.WorldRegionId).First().Name;
        }
    }

    public class OONCountryComparer : IComparer<OONCountry>
    {
        public int Compare(OONCountry x, OONCountry y)
        {
            return string.Compare(x.Name, y.Name);
        }
    }
    public class OONCountry
    {
        public string Name { get; set; }
        public int WorldRegionId { get; set; }
        public int EntryYear { get; set; }
        public static void Main()
        {
            var WorldRegions =  new List<WorldRegion>()
                {
                    new WorldRegion(){Name="Europe", Id=1},
                    new WorldRegion(){ Name="Africa", Id=2},
                    new WorldRegion(){ Name="America", Id=3},
                    new WorldRegion(){Name="Asia", Id=4},
                    new WorldRegion(){ Name="Oceania", Id=5}
                };
            var OONCountries = new List<OONCountry>()
                {
                    new OONCountry{Name="France",  WorldRegionId=1, EntryYear=1945},
                    new OONCountry{Name="Ukraine", WorldRegionId=1, EntryYear=1945},
                    new OONCountry{Name="USA", WorldRegionId=3, EntryYear=1945},
                    new OONCountry{Name="Samoa", WorldRegionId=5, EntryYear=1976},
                    new OONCountry{Name="Kongo", WorldRegionId=2, EntryYear=1960},
                    new OONCountry{Name="Oman", WorldRegionId=4, EntryYear=1971},
                    new OONCountry{Name="Namibia", WorldRegionId=2, EntryYear=1990},
                    new OONCountry{Name="Laos", WorldRegionId=4, EntryYear=1955},
                    new OONCountry{Name="Kirybati", WorldRegionId=5, EntryYear=1999},
                    new OONCountry{Name="Latvia", WorldRegionId=1, EntryYear=1991},
                    new OONCountry{Name="Monako", WorldRegionId=1, EntryYear=1993},
                    new OONCountry{Name="Kanada", WorldRegionId=3, EntryYear=1945},
                    new OONCountry{Name="Spain", WorldRegionId=1, EntryYear=1955},
                    new OONCountry{Name="Italy", WorldRegionId=1, EntryYear=1955},
                    new OONCountry{Name="Katar", WorldRegionId=4, EntryYear=1971},
                    new OONCountry{Name="Mexica", WorldRegionId=3, EntryYear=1945},
                    new OONCountry{Name="Malaysia", WorldRegionId=4, EntryYear=1957},
                };

            Console.WriteLine();
            Console.WriteLine("Ordered by entry year : ");
            Console.WriteLine();
            var sortedCountries = OONCountries.OrderBy(x => x.EntryYear).ToArray();
            foreach (var country in sortedCountries)
            {
                Console.WriteLine("{0} entry in {1} and locates in Asia.", country.Name, country.EntryYear);
            }

            Console.WriteLine();
            Console.WriteLine("Ordered by name with IComparer : ");
            Console.WriteLine();
            var sortedCountries_2 = OONCountries;
            sortedCountries_2.Sort(new OONCountryComparer());
            foreach (var country in sortedCountries_2)
            {
                Console.WriteLine("{0} entry in {1} and locates in Asia.", country.Name, country.EntryYear);
            }

            Console.WriteLine();
            Console.WriteLine("Make dictionary WorldRegionName - List<OONCountry> :");
            Console.WriteLine();
            // Make dictionary WorldRegionName - List<OONCountry>
            var OONCountriesDictionary = OONCountries.GroupBy(x => x.WorldRegionId).
                ToDictionary(x => WorldRegions.Where(m => x.Key == m.Id).First().Name, y => y.OrderBy(z => z.Name).ToList());
            foreach (var (key, countries) in OONCountriesDictionary)
            {
                foreach (var country in countries)
                {
                    Console.WriteLine(String.Format("{0} locates in {1} and entry in OON in {2}", country.Name, key, country.EntryYear));
                }
            }

            Console.WriteLine();
            Console.WriteLine("Prints only selected names :");
            Console.WriteLine();
            // Prints only selected names
            var countriesNames = OONCountries.Select(x => x.Name).ToList();
            foreach (var countryName in countriesNames)
            {
                Console.WriteLine(countryName);
            }

            Console.WriteLine();
            Console.WriteLine("Print countries which is in Asia :");
            Console.WriteLine();
            // Print countries which is in Asia
            var countriesInAsia = OONCountries.Where(x => x.WorldRegionId == WorldRegions.Where(x => x.Name == "Asia").First().Id).ToList();
            foreach (var country in countriesInAsia)
            {
                Console.WriteLine("{0} entry in {1} and locates in Asia.", country.Name, country.EntryYear);
            }

            Console.WriteLine();
            Console.WriteLine("Cast to array and print :");
            Console.WriteLine();
            // Cast to array and print
            var countriesArray = OONCountries.ToArray();
            foreach (var country in countriesArray)
            {
                Console.WriteLine("{0} entry in {1} and locates in {2}.", country.Name, country.EntryYear,
                    country.GetWorldRegionName(WorldRegions));
            }

            Console.WriteLine();
            Console.WriteLine("Order world regions by count of counries in list : ");
            Console.WriteLine();
            var sortedRegions = WorldRegions.OrderBy(x => OONCountries.Where(y => y.WorldRegionId == x.Id).Count()).ToList();
            foreach (var region in sortedRegions)
            {
                Console.WriteLine("{0} with id {1}", region.Name, region.Id);
            }
        }
    }
}
