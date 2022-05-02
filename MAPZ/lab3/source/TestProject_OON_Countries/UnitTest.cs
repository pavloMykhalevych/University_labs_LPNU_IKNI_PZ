using Microsoft.VisualStudio.TestTools.UnitTesting;
using ConsoleApp1;
using System.Collections.Generic;
using System;
using System.Linq;

namespace TestProject_OON_Countries
{
    [TestClass]
    public class UnitTest
    {
        public List<WorldRegion> WorldRegions
        {
            get
            {
                return new List<WorldRegion>()
                {
                    new WorldRegion(){Name="Europe", Id=1},
                    new WorldRegion(){ Name="Africa", Id=2},
                    new WorldRegion(){ Name="America", Id=3},
                    new WorldRegion(){Name="Asia", Id=4},
                    new WorldRegion(){ Name="Oceania", Id=5}
                };
            }
        }

        // Specify the second data source.
        public List<OONCountry> OONCountries
        {
            get
            {
                return new List<OONCountry>()
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
                    new OONCountry{Name="Malaysia", WorldRegionId=4, EntryYear=1957}
                };
            }
        }

        [TestMethod]
        public void TestMethod1()
        {
            int expectedCountInEurope = 6;
            Assert.AreEqual(expectedCountInEurope, OONCountries.Where(x => x.WorldRegionId == WorldRegions.Where(x => x.Name == "Europe").First().Id).Count());
        }

        [TestMethod]
        public void TestMethod2()
        {
            int expectedCountInEurope = 4;
            Assert.AreEqual(expectedCountInEurope, OONCountries.Where(x => x.WorldRegionId == WorldRegions.Where(x => x.Name == "Asia").First().Id).Count());
        }

        [TestMethod]
        public void TestMethod3()
        {
            var expectedSortedOONCountries = new List<OONCountry>()
                {
                    new OONCountry{Name="France",  WorldRegionId=1, EntryYear=1945},
                    new OONCountry{Name="Italy", WorldRegionId=1, EntryYear=1955},
                    new OONCountry{Name="Kanada", WorldRegionId=3, EntryYear=1945},
                    new OONCountry{Name="Katar", WorldRegionId=4, EntryYear=1971},
                    new OONCountry{Name="Kirybati", WorldRegionId=5, EntryYear=1999},
                    new OONCountry{Name="Kongo", WorldRegionId=2, EntryYear=1960},
                    new OONCountry{Name="Laos", WorldRegionId=4, EntryYear=1955},
                    new OONCountry{Name="Latvia", WorldRegionId=1, EntryYear=1991},
                    new OONCountry{Name="Malaysia", WorldRegionId=4, EntryYear=1957},
                    new OONCountry{Name="Mexica", WorldRegionId=3, EntryYear=1945},
                    new OONCountry{Name="Monako", WorldRegionId=1, EntryYear=1993},
                    new OONCountry{Name="Namibia", WorldRegionId=2, EntryYear=1990},
                    new OONCountry{Name="Oman", WorldRegionId=4, EntryYear=1971},
                    new OONCountry{Name="Samoa", WorldRegionId=5, EntryYear=1976},
                    new OONCountry{Name="Spain", WorldRegionId=1, EntryYear=1955},
                    new OONCountry{Name="Ukraine", WorldRegionId=1, EntryYear=1945},
                    new OONCountry{Name="USA", WorldRegionId=3, EntryYear=1945},
                };
            expectedSortedOONCountries.Sort(new OONCountryComparer());
            var sorted = OONCountries.OrderBy(x => x.Name).ToList();
            var comparer = new OONCountryComparer();
            for (int i = 0; i < expectedSortedOONCountries.Count; ++i)
            {
                Assert.AreEqual(expectedSortedOONCountries[i].Name, sorted[i].Name);
            }
        }
        [TestMethod]
        public void TestMethod4()
        {
            var expectedSortedWorldRegions = new List<WorldRegion>()
                {
                    new WorldRegion(){ Name="Africa", Id=2},
                    new WorldRegion(){ Name="Oceania", Id=5},
                    new WorldRegion(){ Name="America", Id=3},
                    new WorldRegion(){Name="Asia", Id=4},
                    new WorldRegion(){Name="Europe", Id=1},
                };
            var sorted = WorldRegions.OrderBy(x => OONCountries.Where(y => y.WorldRegionId == x.Id).Count()).ToList();
            for (int i = 0; i < expectedSortedWorldRegions.Count; ++i)
            {
                Assert.AreEqual(expectedSortedWorldRegions[i].Name, sorted[i].Name);
            }
        }
    }
}
