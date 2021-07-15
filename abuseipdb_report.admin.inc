<?php
/**
 * @file abuseipdb_report.admin.inc
 * Admin form to manage module settings
 *
 */

/**
 * Define the form for manage report
 *
 */
function abuseipdb_report_form($form, &$form_state) {
  $config  = config('abuseipdb_report.settings');
  $api_key = $config->get('abuseipdb_api_key');

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['settings']['abuseipdb_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API key'),
    '#default_value' => $api_key,
    '#size' => 96,
    '#description' => t('The API key provided by AbuseIPDB.') . '<br>'
    . t("Get a <a href='@key'>free API key</a> if you haven't already.", array('@key' => 'https://www.abuseipdb.com/register')),
  );
  $form['settings']['log_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable logging'),
    '#default_value' => $config->get('log_enabled'),
    '#description' => t('Enable logging of module activity.'),
  );
  $form['settings']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
    '#attributes' => array(
      'class' => array('button-primary'),
    ),
  );

  $form['report_now'] = array(
    '#type' => 'fieldset',
    '#title' => t('Report abusive IP now'),
    '#collapsible' => TRUE,
    '#collapsed' => empty($api_key) ? TRUE : FALSE,
    '#disabled' => empty($api_key) ? TRUE : FALSE,
    '#description' => t('You can report an IP directly to AbuseIPDB by using form below.'),
  );
  $form['report_now']['ip'] = array(
    '#title' => t('IP address to report'),
    '#type' => 'textfield',
    '#size' => 48,
    '#maxlength' => 40,
    '#description' => t('Enter a valid IP address to be reported.'),
  );
  $form['report_now']['comment'] = array(
    '#type' => 'textarea',
    '#title' => t('Comment'),
    '#description' => t('Malicious activity do you want to report, e.g. server log snippets, abuse details, etc.'),
  );

  $categories = abuseipdb_report_categories();
  $names      = array();

  foreach ($categories as $key => $value) {
    $names[$key] = $value['name'];
  }

  $form['report_now']['categories'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Categories'),
    '#options' => $names,
    '#default_value' => array(21), // Web App Attack
  );
  $form['report_now']['report'] = array(
    '#type' => 'submit',
    '#value' => t('Report IP now'),
    '#attributes' => array(
      'class' => array('button-primary'),
    ),
    '#validate' => array('abuseipdb_report_form_validate_report'),
  );

  return $form;
}

/**
 * Implements hook_form_FORM_ID_alter().
 * Add description for each checkbox.
 */
function abuseipdb_report_form_abuseipdb_report_form_alter(&$form, &$form_state, $form_id) {
  $categories = abuseipdb_report_categories();

  foreach($form['report_now']['categories']['#options'] as $key => $value) {
    $form['report_now']['categories'][$key]['#description'] = $categories[$key]['description'];
  }
}

/**
 * Implements form custom validate.
 */
function abuseipdb_report_form_validate_report($form, &$form_state) {
  $ip         = trim($form_state['values']['ip']);
  $comment    = trim($form_state['values']['comment']);
 	$categories = current($form_state['values']['categories']);

  if ($ip == ip_address()) {
    form_set_error('ip', t('You are trying to report your IP address.'));
  }
  elseif (filter_var($ip, FILTER_VALIDATE_IP, FILTER_FLAG_NO_RES_RANGE) == FALSE) {
    form_set_error('ip', t('Enter a valid IP address.'));
  }

  if (strlen($comment) < 3) {
    form_set_error('comment', t('Descriptive comment is required.'));
  }

  if (empty($categories)) {
    form_set_error('categories', t('At least one category must be selected.'));
  }
}


/**
 * Implements hook_submit().
 */
function abuseipdb_report_form_submit($form, &$form_state) {
  global $user;
  $config = config('abuseipdb_report.settings');

  if ($form_state['clicked_button']['#id'] == 'edit-submit') {
    $config->set('abuseipdb_api_key', trim($form_state['values']['abuseipdb_api_key']));
    $config->set('log_enabled',       $form_state['values']['log_enabled']);

    $config->save();
    watchdog('abuseipdb_report', t('Settings changed by @user.', array('@user' => $user->name)));
    backdrop_set_message(t('Settings have been saved.'));
  }
  else {
    $ip         = $form_state['values']['ip'];
    $comment    = trim($form_state['values']['comment']);
    $categories = $form_state['values']['categories'];

    abuseipdb_report_ip($ip, $comment, '"AbuseIPDB report" module', array_filter($categories));
    backdrop_set_message(t('IP @ip have been reported, you can see the result on the <a href="@log">log page</a>.',
      array(
        '@ip' => $ip, 
        '@log' => url('admin/reports/dblog'),
      )         
    ));
  }
}
