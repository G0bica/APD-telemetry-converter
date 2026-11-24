> For the complete documentation index, see [llms.txt](https://docs.powerdrives.net/llms.txt). Markdown versions of documentation pages are available by appending `.md` to page URLs; this page is available as [Markdown](https://docs.powerdrives.net/products/f_series/f-series-configuration.md).

# F Series Configuration Options

This section of the guide outlines the various configurable elements of the F\_Series through the configuration tool, along with their default settings.

{% hint style="warning" %}
These configuration options are for units running F\_Series firmware 2.3.0 or later.
{% endhint %}

## Mode

Loads the configurator tool fields with the recommended settings for the desired drivetrain application. Two mode options exist, Normal mode and Reversible mode.

{% hint style="info" %}
Default setting is: Normal
{% endhint %}

## Motor Drive Settings

Motor drive specific settings.

### Motor Direction

The desired direction in which the motor should operate.&#x20;

{% hint style="info" %}
Default setting is: Normal
{% endhint %}

### Motor Start Power&#x20;

The intensity of the initial voltage applied to the motor when spooling up from stand-still.

{% hint style="info" %}
Default setting is: Normal
{% endhint %}

### Timing Advance

Increased timing advance can reduce ESC running temperatures for some motors. The recommended setting is auto.

{% hint style="info" %}
Default setting is: Auto
{% endhint %}

## Throttle

Throttle specific settings.

### **Ramp Up/Down Settings**

Acceleration and braking rates for the ESC, which are applied on every change of throttle input to the ESC.

{% hint style="info" %}
Default setting is: 50% for both
{% endhint %}

### Deadzone Percentage

Sets the middle dead zone when using reversible mode. Taken as a percentage of the endpoint range.

{% hint style="info" %}
Default setting is: 0%
{% endhint %}

## ESC Limits

Settings related to the limits of the ESC and responses.&#x20;

### Bus Current Limit

The upper current limit the ESC can reach on the input from the power supply. Configurable from 150 to 200 Amps, depending on the ESC model.

{% hint style="info" %}
Default setting is: Maximum for the ESC model
{% endhint %}

### Temperature Limit

The temperature limit for the ESC as measured internally. Configurable to ranges from 70 to 120 degrees Celsius.

{% hint style="info" %}
Default setting is: 120 degrees C
{% endhint %}

### Over-temperature Response

The requested ESC response to an over-temperature event.

{% hint style="info" %}
Default setting is: 50% Throttle
{% endhint %}

## Additional Settings

Advanced settings for the ESC.

### Input Signal Type

Set the current input signal type to be used by the ESC for throttle input. Affects telemetry output in certain scenarios.

{% hint style="info" %}
Default setting is: Auto
{% endhint %}

### DShot Baud Type

Select the DShot rate to use, when using DShot as signal type.

{% hint style="info" %}
Default setting is: Auto
{% endhint %}

### Telemetry Enabled

Toggle the output of telemetry on T pin. The telemetry output format will be dictated by the type setting.

{% hint style="info" %}
Default setting is: Enabled
{% endhint %}

### Telemetry Type

Change the type of telemetry that is output by the T pin on the ESC. The options are:&#x20;

**DShot/Betaflight Telemetry**: Standard DShot telemetry format used by most flight controllers. Requires a DShot signal input to request the telemetry before it is transmitted.

**PWM Telemetry**: Forces the output of the DShot telemetry format at 1Hz. Each transmission is terminated with 2 stop bytes, and has the following format:

![PWM telemetry format](https://1013232572-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-LqA1iwil1ddpVBXp8FT%2Fuploads%2F83U8Xwg3lO8m3wfqhcvc%2FPWM_Telem_v2.png?alt=media\&token=dc31d345-129c-4c5e-93a1-9c8f080712c3)

**RPM Output**: Outputs a pulse for each complete electrical revolution of the motor. Pulses per minute indicate electrical RPM, which can be converted to mechanical RPM by dividing with the motors pole pairs. This can be used with Governor systems.

{% hint style="info" %}
Default setting is: DShot/Betaflight Telemetry
{% endhint %}

### F5B Startup

Improve initial starting rates for F5B use cases. Warning, this mode should not be used with large propellors as it may result in large current loads immediately on startup.

{% hint style="info" %}
Default setting is: Disabled
{% endhint %}

### Brake on Stop

Toggles whether the ESC will forcefully brake the motor when a zero command is given (enabled), or allowing the motor to freewheel to a stop (disabled).

{% hint style="info" %}
Default setting is: Enabled
{% endhint %}

### Motor Beep Tones

Change the audible beeps from the motor, either completely off or specific selections.

{% hint style="info" %}
Default setting is: All Beep Tones
{% endhint %}

### Auto Detect Endpoints

Automatically set the endpoints that are used when the ESC is driven using a PWM input throttle signal. Disable and adjust manually if desired.

{% hint style="info" %}
Default setting is: Enabled
{% endhint %}
