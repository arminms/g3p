---
title: API Reference
subtitle: Namespaces, Classes and Functions
subject: g3p API Reference
description: G3P API Reference.
---

# API Reference

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`namespace `[`g3p`](#namespace_g3p) | `g3p` _namespace_

::::{dropdown}
:open:

(namespace_g3p)=
## namespace `g3p` 

The main namespace of G3P library.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`static const std::string `[`end`](#end_manipulator) | `g3p::end` manipulator
`static const std::string `[`endl`](#endl_manipulator) | `g3p::endl` manipulator
`static const std::string `[`eod`](#eod_manipulator) | `g3p::eod` manipulator
` const std::string `[`flush`](#flush_manipulator) | `g3p::flush` manipulator
`template<>`  <br/>`std::string `[`make_data_block`](#make_data_block_2)`(const `[`gnuplot`](#class_gnuplot)`& gp, const T& c)` | Returns a data block for the gnuplot instance
`template<>`  <br/>`std::string `[`make_data_block`](#make_data_block_4)`(const `[`gnuplot`](#class_gnuplot)`& gp,const T& c, typename T::size_type row, typename T::size_type sep)` | Returns a data block for the gnuplot instance
`nlohmann::json `[`mime_bundle_repr`](#mime_bundle_repr)`(const `[`gnuplot`](#class_gnuplot)` & gp)` | Overloaded function for mime representation in a Jupyter Notebook's cell (_only available in `cling`_)
`void `[`display`](#display_func)`(const `[`gnuplot`](#class_gnuplot)`& gp,bool clear_ouput)` | Displays the gnuplot in the notebook (_only available in `cling`_)
`class `[`gnuplot`](#class_gnuplot) | Encapsulation of a <wiki:Gnuplot> instance

### Members

:::{dropdown}
:open:

(end_manipulator)=
#### `static const std::string `[`end`](#end_manipulator)

Manipulator for sending end-of-data stream signal to <wiki:Gnuplot> instance.

:::

:::{dropdown}
:open:

(endl_manipulator)=
#### `static const std::string `[`endl`](#endl_manipulator)

Manipulator for sending end of line character and flushing the buffer.

:::

:::{dropdown}
:open:

(eod_manipulator)=
#### `static const std::string `[`eod`](#eod_manipulator)

Manipulator for sending start/end of a datablock to <wiki:Gnuplot> instance.

:::

:::{dropdown}
:open:

(flush_manipulator)=
#### `static const std::string `[`flush`](#eod_manipulator)

Manipulator for flushing the buffer.

:::

:::{dropdown}
:open:

(make_data_block_2)=
#### `template<T>`  <br/>`std::string `[`make_data_block`](#make_data_block_2)`(const `[`gnuplot`](#class_gnuplot)`& gp, const T& c)` 

Helper function that returns a data block for the gnuplot instance.

|Type Parameters||
|-|-|
|`T`|Type of the object to be converted to a data block|

|Parameters||
|-|-|
|`gp`|Reference to the gnuplot instance|
|`c`|Reference to the object to be converted to a data block|

|Return||
|-|-|
|`std::string`|A string representing the name of the data block|

:::

:::{dropdown}
:open:

(make_data_block_4)=
#### `template<T>`  <br/>`std::string `[`make_data_block`](#make_data_block_4)`(const `[`gnuplot`](#class_gnuplot)`& gp, const T& c, typename T::size_type row, typename T::size_type sep)` 

Helper function that returns a data block for the gnuplot instance.

|Type Parameters||
|-|-|
|`T`|Type of the container to be converted to a data block|

|Parameters||
|-|-|
|`gp`|Reference to the gnuplot instance|
|`c`|Reference to the container to be converted to a data block|
|`row`|Number of elements in each row|
|`sep`|Number of rows to separate the data block|

|Return||
|-|-|
|`std::string`|A string representing the name of the data block|

:::

:::{dropdown}
:open:

(mime_bundle_repr)=
#### `nlohmann::json `[`mime_bundle_repr`](#mime_bundle_repr)`(const `[`gnuplot`](#class_gnuplot)`& gp)` 

Overloaded function for mime representation in a Jupyter Notebook's cell (_only available in `cling`_)

|Parameters||
|-|-|
|`gp`|Constant reference to a gnuplot instance|

|Return||
|-|-|
|`nlohmann::json`|A json mime representation|

:::

:::{dropdown}
:open:

(display_func)=
#### `void `[`display`](#display_func)`(const `[`gnuplot`](#class_gnuplot)`& gp, bool clear_ouput)`

Displays the gnuplot in the notebook (_only available in `cling`_).

|Parameters||
|-|-|
|`gp`|Reference to the gnuplot instance|
|`clear_output`|A boolean indicating whether the output should be cleared (_default_ = `true`)|

:::

::::

::::{dropdown}
:open:

(class_gnuplot)=
## class `gnuplot`

The one and only class in G3P that encapsulates a <wiki:Gnuplot> instance.

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
` `[`gnuplot`](#gnuplot_constructor)`(bool persist,std::string logfile)` | Default constructor
` `[`~gnuplot`](#gnuplot_destructor)`()` | Destructor
`double `[`version`](#gnuplot_version)`()` | Returns the version of gnuplot excluding the patchlevel
`std::string `[`version_string`](#gnuplot_version_string)`()` | Returns the version and patchlevel of gnuplot
`std::string `[`patchlevel`](#gnuplot_patchlevel)`()` | Returns the patchlevel of gnuplot
`std::string `[`log`](#gnuplot_log)`(size_t line_count) const` | Returns the content of the log file
`std::string `[`plotfile`](#gnuplot_plotfile)`() const` | Returns the name of the plot file (_only available in `cling`_)
`const `[`gnuplot`](#class_gnuplot)`& `[`sync`](#gnuplot_sync)`() const` | Waits for the gnuplot to finish processing the commands
`template<>`  <br/>`const `[`gnuplot`](#class_gnuplot)`& `[`operator()`](#gnuplot_fn_operator)`(Args &&... args) const` | Sends the arguments to the gnuplot instance
`template<>`  <br/>`const `[`gnuplot`](#class_gnuplot)`& `[`operator<<`](#gnuplot_in_operator)`(T arg) const` | Sends the argument to the gnuplot instance
`std::istringstream `[`operator>>`](#gnuplot_out_operator)`(size_t line_count) const` | Reads the output of the gnuplot instance
`const `[`gnuplot`](#class_gnuplot)`& `[`endl`](#gnuplot_endl)`() const` | Sends an end-of-line to the gnuplot instance
`const `[`gnuplot`](#class_gnuplot)`& `[`end`](#gnuplot_end)`() const` | Sends an end-of-data to the gnuplot instance
`const `[`gnuplot`](#class_gnuplot)`& `[`flush`](#gnuplot_flush)`() const` | Sends a flush command to the gnuplot instance

### Members

:::{dropdown}
:open:

(gnuplot_constructor)=
#### ` `[`gnuplot`](#gnuplot_constructor)`(bool persist, std::string logfile)` 

Default constructor

|Parameters||
|-|-|
|`persist`|A boolean indicating whether the gnuplot instance should be persistent (_default_ = `true`)|
|`logfile`|A string representing the name of the log file (_default_ = `{}`)|

:::

:::{dropdown}
:open:

(gnuplot_destructor)=
#### ` `[`~gnuplot`](#gnuplot_destructor)`()` 

Destructor

:::

:::{dropdown}
:open:

(gnuplot_version)=
#### `double `[`version`](#gnuplot_version)`()` 

Returns the version of gnuplot excluding the patchlevel

|Return||
|-|-|
|`double`|A double representing the version of gnuplot|

:::

:::{dropdown}
:open:

(gnuplot_version_string)=
#### `std::string `[`version_string`](#gnuplot_version_string)`()` 

Returns the version and patchlevel of gnuplot

|Return||
|-|-|
|`std::string`|A string representing the version and patchlevel of gnuplot|

:::

:::{dropdown}
:open:

(gnuplot_patchlevel)=
#### `std::string `[`patchlevel`](#gnuplot_patchlevel)`()` 

Returns the patchlevel of gnuplot

|Return||
|-|-|
|`std::string`|A string representing the patchlevel of gnuplot|

:::

:::{dropdown}
:open:

(gnuplot_log)=
#### `std::string `[`log`](#gnuplot_log)`(size_t line_count) const` 

Returns the content of the log file

|Parameters||
|-|-|
|`line_count`|Number of lines to return from the end of the log file. The whole log file if `0`. (_default_ = `0`)|

|Return||
|-|-|
|`std::string`|A string representing the content of the log file|

:::

:::{dropdown}
:open:

(gnuplot_plotfile)=
#### `std::string `[`plotfile`](#gnuplot_plotfile)`() const` 

Returns the name of the plot file (_only available in `cling`_)

|Return||
|-|-|
|`std::string`|A string representing the name of the plot file|

:::

:::{dropdown}
:open:

(gnuplot_sync)=
#### `const `[`gnuplot`](#class_gnuplot)`& `[`sync`](#gnuplot_sync)`() const` 

Waits for the gnuplot to finish processing the commands

|Return||
|-|-|
|`const `[`gnuplot`](#class_gnuplot)`&`|A constant reference to the gnuplot object|

:::

:::{dropdown}
:open:

(gnuplot_fn_operator)=
#### `template<>`  <br/>`const `[`gnuplot`](#class_gnuplot)`& `[`operator()`](#gnuplot_fn_operator)`(Args &&... args) const` 

Sends the arguments to the gnuplot instance

|Parameters||
|-|-|
|`args`|Arguments to be sent to the gnuplot instance|

|Return||
|-|-|
|`const `[`gnuplot`](#class_gnuplot)`&`|A constant reference to the gnuplot object|

:::

:::{dropdown}
:open:

(gnuplot_in_operator)=
#### `template<>`  <br/>`const `[`gnuplot`](#class_gnuplot)`& `[`operator<<`](#gnuplot_in_operator)`(T arg) const` 

Sends the argument to the gnuplot instance

|Parameters||
|-|-|
|`arg`|Argument to be sent to the gnuplot instance|

|Return||
|-|-|
|`const `[`gnuplot`](#class_gnuplot)`&`|A constant reference to the gnuplot object||

:::

:::{dropdown}
:open:

(gnuplot_out_operator)=
#### `std::istringstream `[`operator>>`](#gnuplot_out_operator)`(size_t line_count) const` 

Reads the output of the gnuplot instance

|Parameters||
|-|-|
|`line_count`|Number of lines to read from the end of the output|

|Return||
|-|-|
|`std::istringstream`|A stringstream containing the output of the gnuplot instance|

:::

:::{dropdown}
:open:

(gnuplot_endl)=
#### `const `[`gnuplot`](#class_gnuplot)`& `[`endl`](#gnuplot_endl)`() const` 

Sends an end-of-line to the gnuplot instance

|Return||
|-|-|
|`const `[`gnuplot`](#class_gnuplot)`&`|A constant reference to the gnuplot object|

:::

:::{dropdown}
:open:

(gnuplot_end)=
#### `const `[`gnuplot`](#class_gnuplot)`& `[`end`](#gnuplot_end)`() const` 

Sends an end-of-data to the gnuplot instance

|Return||
|-|-|
|`const `[`gnuplot`](#class_gnuplot)`&`|A constant reference to the gnuplot object|

:::

:::{dropdown}
:open:

(gnuplot_flush)=
#### `const `[`gnuplot`](#class_gnuplot)`& `[`flush`](#gnuplot_flush)`() const` 

Sends a flush command to the gnuplot instance

|Return||
|-|-|
|`const `[`gnuplot`](#class_gnuplot)`&`|A constant reference to the gnuplot object|

:::

::::