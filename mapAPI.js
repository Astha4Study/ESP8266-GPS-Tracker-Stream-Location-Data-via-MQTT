var map = L.map('map').setView([0, 0], 15);
L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
  attribution: '© OpenStreetMap contributors'
}).addTo(map);

// Function to fetch data from the API
function fetchData() {
  // Replace 'YOUR_API_ENDPOINT' with the actual API endpoint
  var apiUrl = 'https://api.thingspeak.com/channels/2734969/feeds/last.json?timezone=Asia%2FJakarta&api_key=L1UTZJ0ZKDA8K5ZH';

  // Fetch data from the API
  fetch(apiUrl)
    .then(response => response.json())
    .then(data => {
      // Update the map with the new data
      console.log('Response JSON:', data);
      updateMarker(data);
    })
    .catch(error => console.error('Error fetching data:', error));
}

// Function to update markers on the map
function updateMarker(location) {
 var latLng = [parseFloat(location.field1), parseFloat(location.field2)];
  // Remove existing marker
  map.eachLayer(function (layer) {
    if (layer instanceof L.Marker) {
      map.removeLayer(layer);
    }
  });

  // Add new marker based on the API response
  var marker = L.marker([parseFloat(location.field1), parseFloat(location.field2)])
    .addTo(map);
  map.setView(latLng, map.getZoom());
}

// Initial fetch when the page loads
fetchData();

// Fetch data every 10 seconds (adjust the interval as needed)
setInterval(fetchData, 10000);

