
export function createCheckboxesForEvents(venues, eventTypes) {
    const venueCheckboxes = venues.map(venue => `
      <label class="checkbox-label">
        <input type="radio" name="venue" value="${venue.id}" class="venue-checkbox">
        ${venue.name}
      </label>
    `).join('');
  
    const eventTypeCheckboxes = eventTypes.map(eventType => `
      <label class="checkbox-label">
        <input type="radio" name="eventType" value="${eventType}" class="event-type-checkbox">
        ${eventType}
      </label>
    `).join('');
  
    return `
      <div class="filter-options">
        <h3>Filter by Venue:</h3>
        ${venueCheckboxes}
      </div>
      <div class="filter-options">
        <h3>Filter by Event Type:</h3>
        ${eventTypeCheckboxes}
      </div>
      <button id="apply-filter-btn" class="filter-btn">Apply Filter</button>
    `;
  }
  