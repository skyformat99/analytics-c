
//
// analytics.c
//
// Copyright (c) 2017 Segment
//

#include <stdlib.h>
#include <assert.h>
#include "analytics.h"

/**
 * Initialize with `write_key`.
 */

analytics_t *
analytics_init(const char *write_key) {
  assert(write_key);

  analytics_t *self;
  if (!(self = malloc(sizeof(analytics_t)))) {
    return NULL;
  }

  self->write_key = write_key;
  self->host = "https://api.segment.com";

  return self;
}

/**
 * Free up analytics after use.
 */

void
analytics_free(analytics_t *self) {
  free(self);
  self = NULL;
}

/**
 * Create a new analytics event.
 */

analytics_event_t *
analytics_event_new (analytics_method_t type) {
  analytics_event_t *event;

  if (!(event = malloc(sizeof(analytics_event_t)))) {
    return NULL;
  }

  event->method = type;

  event->event = NULL;
  event->name = NULL;

  event->group_id = NULL;
  event->user_id = NULL;
  event->anonymous_id = NULL;
  event->previous_id = NULL;

  event->traits = NULL;
  event->properties = NULL;

  return event;
}

void
analytics_event_free(analytics_event_t *event) {
  free(event);
}

/**
 * Track.
 */

int
analytics_track(analytics_t *self, const char *event_name, const char *user_id, analytics_hashmap_t *properties) {
  analytics_event_t *event = analytics_event_new(ANALYTICS_METHOD_TRACK);

  if (!event) {
    return ANALYTICS_MEMORY_ERROR;
  }

  event->event = event_name;
  event->user_id = user_id;

  return ANALYTICS_SUCCESS;
}

/**
 * Identify.
 */

int
analytics_identify(analytics_t *self, const char *user_id, analytics_hashmap_t *traits) {
  analytics_event_t *event = analytics_event_new(ANALYTICS_METHOD_IDENTIFY);

  if (!event) {
    return ANALYTICS_MEMORY_ERROR;
  }

  event->user_id = user_id;
  event->traits = traits;

  return ANALYTICS_SUCCESS;
}

/**
 * Page.
 */

int
analytics_page(analytics_t *self, const char *event_name, const char *userId, analytics_hashmap_t *properties) {
  analytics_event_t *event = analytics_event_new(ANALYTICS_METHOD_PAGE);

  if (!event) {
    return ANALYTICS_MEMORY_ERROR;
  }

  event->name = event_name;
  event->properties = properties;

  return ANALYTICS_SUCCESS;
}

/**
 * Screen.
 */

int
analytics_screen(analytics_t *self, const char *event_name, const char *userId, analytics_hashmap_t *properties) {
  analytics_event_t *event = analytics_event_new(ANALYTICS_METHOD_SCREEN);

  if (!event) {
    return ANALYTICS_MEMORY_ERROR;
  }

  event->name = event_name;
  event->properties = properties;

  return ANALYTICS_SUCCESS;
}

/**
 * Alias.
 */

int
analytics_alias(analytics_t *self, const char *previous_id, const char *user_id) {
  analytics_event_t *event = analytics_event_new(ANALYTICS_METHOD_ALIAS);

  if (!event) {
    return ANALYTICS_MEMORY_ERROR;
  }

  event->previous_id = previous_id;
  event->user_id = user_id;

  return ANALYTICS_SUCCESS;
}

/**
 * Group.
 */

int
analytics_group(analytics_t *self, const char *group_id, analytics_hashmap_t *traits) {
  analytics_event_t *event = analytics_event_new(ANALYTICS_METHOD_GROUP);

  if (!event) {
    return ANALYTICS_MEMORY_ERROR;
  }

  event->group_id = group_id;
  event->traits = traits;

  return ANALYTICS_SUCCESS;
}
