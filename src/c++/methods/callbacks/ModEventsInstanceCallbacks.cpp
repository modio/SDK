#include "c++/methods/callbacks/ModEventsInstanceCallbacks.h"
#include "c++/schemas/Response.h"

namespace modio
{
std::map<u32, GetEventsCall *> get_events_calls;
std::map<u32, GetAllEventsCall *> get_all_events_calls;
SetEventListenerCall *set_event_listener_call;

void onGetEvents(void *object, ModioResponse modio_response, ModioModEvent *events_array, u32 events_array_size)
{
  u32 call_id = (u32)((uintptr_t)object);

  modio::Response response;
  response.initialize(modio_response);

  std::vector<modio::ModEvent> event_vector;
  event_vector.resize(events_array_size);
  for (u32 i = 0; i < events_array_size; i++)
  {
    event_vector[i].initialize(events_array[i]);
  }
  get_events_calls[call_id]->callback(response, event_vector);

  delete get_events_calls[call_id];
  get_events_calls.erase(call_id);
}

void onGetAllEvents(void *object, ModioResponse modio_response, ModioModEvent *events_array, u32 events_array_size)
{
  u32 call_id = (u32)((uintptr_t)object);

  modio::Response response;
  response.initialize(modio_response);

  std::vector<modio::ModEvent> event_vector;
  event_vector.resize(events_array_size);
  for (u32 i = 0; i < events_array_size; i++)
  {
    event_vector[i].initialize(events_array[i]);
  }
  get_all_events_calls[call_id]->callback(response, event_vector);

  delete get_all_events_calls[call_id];
  get_all_events_calls.erase(call_id);
}

void onSetEventListener(ModioResponse modio_response, ModioModEvent *events_array, u32 events_array_size)
{
  modio::Response response;
  response.initialize(modio_response);

  std::vector<modio::ModEvent> events_vector;
  events_vector.resize(events_array_size);
  for (u32 i = 0; i < events_array_size; i++)
  {
    events_vector[i].initialize(events_array[i]);
  }
  set_event_listener_call->callback(response, events_vector);
}

void clearModEventsRequestCalls()
{
  for (auto get_events_call : get_events_calls)
    delete get_events_call.second;
  get_events_calls.clear();

  for (auto get_all_events_call : get_all_events_calls)
    delete get_all_events_call.second;
  get_all_events_calls.clear();
}
} // namespace modio
