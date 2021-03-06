<?php
/**
 * @file
 * Process output text.
 */

/**
 * @defgroup outputfunctions
 * @{
 */

/**
 * Prints a message with optional indentation.
 *
 * In general, drush_log($message, LogLevel::OK) is often a better choice than
 * this function. That gets your confirmation message (for example) into the
 * logs for this drush request. Consider that drush requests may be executed
 * remotely and non interactively.
 *
 * @param string $message
 *   The message to print.
 * @param int $indent
 *   The indentation (space chars).
 * @param null|int $handle
 *   File handle to write to. NULL will write to standard output, STDERR will
 *   write to the standard error. See
 *   http://php.net/manual/en/features.commandline.io-streams.php
 * @param bool $newline
 *   Add a "\n" to the end of the output. Defaults to TRUE.
 */
function drush_print($message = '', $indent = 0, $handle = NULL, $newline = TRUE) {
  $msg = str_repeat(' ', $indent) . (string) $message;
  if ($newline) {
    $msg .= "\n";
  }
  if (($charset = drush_get_option('output_charset')) && function_exists('iconv')) {
    $msg = iconv('UTF-8', $charset, $msg);
  }
  if (isset($handle)) {
    fwrite($handle, $msg);
  }
  else {
    print $msg;
  }
}

/**
 * Print a prompt -- that is, a message with no trailing newline.
 */
function drush_print_prompt($message, $indent = 0, $handle = NULL) {
  drush_print($message, $indent, $handle, FALSE);
}

/**
 * Print a formatted table.
 *
 * @param array $rows
 *   The rows to print.
 * @param bool $header
 *   If TRUE, the first line will be treated as table header.
 *
 * @return object
 *   Use $tbl->getTable() to get the output from the return value.
 */
function drush_print_table($rows, $header = FALSE) {
  if ($header) {
    $header = array_shift($rows);
  }
  b_render(array(
    '#type' => 'table',
    'rows' => $rows,
    'header' => $header,
    'delimiter' => '  :  ',
    'delimiter_left' => ' ',
    'delimiter_right' => ' ',
  ));
}
