#include "tpl-channel-test.h"

#include <telepathy-logger/channel-factory.h>
#include <telepathy-logger/observer.h>

static gint factory_counter = 0;

static TplChannel *
mock_factory (const gchar *chan_type,
    TpConnection *conn, const gchar *object_path, GHashTable *tp_chan_props,
    TpAccount *tp_acc, GError **error)
{
  factory_counter += 1;
  return NULL;
}



int
main (int argc, char **argv)
{
  TplObserver *obs, *obs2;
  TplChannel *chan;

  g_type_init ();

  obs = tpl_observer_new ();

  /* TplObserver is a singleton, be sure both references point to the same
   * memory address  */
  obs2 = tpl_observer_new ();
  g_assert (obs == obs2);

  /* unref the second singleton pointer and check that the it is still
   * valid: checking correct object ref-counting after each _dup() call */
  g_object_unref (obs2);
  g_assert (TPL_IS_OBSERVER (obs));

  /* it points to the same mem area, it should be still valid */
  g_assert (TPL_IS_OBSERVER (obs2));

  /* register a ChanFactory and test ObserveChannel() */
  tpl_observer_set_channel_factory (obs, mock_factory);


  /* register a channel */
  chan = TPL_CHANNEL (tpl_channel_test_new (NULL, NULL, NULL, NULL, NULL));
  tpl_observer_register_channel (obs, chan);

  /* proper disposal for the singleton when no references are present */
  g_object_unref (obs);
  g_assert (TPL_IS_OBSERVER (obs) == FALSE);

  return 0;
}
