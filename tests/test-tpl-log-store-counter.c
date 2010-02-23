#include <telepathy-logger/log-store-counter.h>
#include <telepathy-logger/debug.h>

int
main (int argc, char **argv)
{
  TplLogStore *store;
  TpDBusDaemon *bus;
  TpAccount *account;
  GError *error = NULL;

  g_type_init ();

  tpl_debug_set_flags_from_env ();

  bus = tp_dbus_daemon_dup (&error);
  g_assert_no_error (error);

  account = tp_account_new (bus,
      TP_ACCOUNT_OBJECT_PATH_BASE "gabble/jabber/danielle_2emadeley_40collabora_2eco_2euk0",
      &error);
  g_assert_no_error (error);

  store = tpl_log_store_counter_dup ();

  g_print ("freq = %g\n",
      tpl_log_store_counter_get_frequency (TPL_LOG_STORE_COUNTER (store),
        account, "dannielle.meyer@gmail.com"));

  g_object_unref (store);
  g_object_unref (account);
  g_object_unref (bus);
}