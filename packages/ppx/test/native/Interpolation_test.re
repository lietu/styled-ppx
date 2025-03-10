open Setup;
open Ppxlib;
let loc = Location.none;

let compare = (input, expected, {expect, _}) => {
  let result = Pprintast.string_of_expression(input);
  let expected = Pprintast.string_of_expression(expected);
  expect.string(result).toEqual(expected);
};

let properties_variable_css_tests = [
  (
    [%expr [%css "color: $(mono100);"]],
    [%expr CssJs.color(mono100)]
  ),
  (
    [%expr [%css "margin: $(Size.big) $(Size.small);"]],
    [%expr CssJs.margin2(~v=Size.big, ~h=Size.small)]
  ),
  (
    [%expr [%css "color: $(mono100);"]],
    [%expr CssJs.color(mono100)]
  ),
  (
    [%expr [%css "padding: $(Size.small) 0px;"]],
    [%expr CssJs.padding2(~v=Size.small, ~h=`pxFloat(0.))]
  ),
  (
    [%expr [%css "border: 1px solid $(Color.Border.alpha);"]],
    [%expr CssJs.border(`pxFloat(1.), `solid, Color.Border.alpha)]
  ),
  (
    [%expr [%css "border-bottom: 0px solid $(Color.Border.alpha);"]],
    [%expr CssJs.borderBottom(`pxFloat(0.), `solid, Color.Border.alpha)]
  ),
  (
    [%expr [%css "width: $(width);"]],
    [%expr CssJs.width(width)]
  ),
  (
    [%expr [%css "max-width: $(max);"]],
    [%expr CssJs.maxWidth(max)]
  ),
  (
    [%expr [%css "height: $(height);"]],
    [%expr CssJs.height(height)]
  ),
  (
    [%expr [%css "border-radius: $(border);"]],
    [%expr CssJs.borderRadius(border)]
  ),
  (
    [%expr [%css "font-size: $(font);"]],
    [%expr CssJs.fontSize(font)]
  ),
  (
    [%expr [%css "font-family: $(mono);"]],
    [%expr CssJs.fontFamily(mono)]
  ),
  (
    [%expr [%css "line-height: $(lh);"]],
    [%expr CssJs.lineHeight(lh)]
  ),
  (
    [%expr [%css "z-index: $(zLevel);"]],
    [%expr CssJs.zIndex(zLevel)]
  ),
  (
    [%expr [%css "left: $(left);"]],
    [%expr CssJs.left(left)]
  ),
  (
    [%expr [%css "text-decoration-color: $(decorationColor);"]],
    [%expr CssJs.textDecorationColor(decorationColor)]
  ),
  /* Changed properties */
  (
    [%expr [%css "box-shadow: $(h) $(v) $(blur) $(spread) $(color);"]],
    [%expr CssJs.boxShadows([|
      CssJs.Shadow.box(~x=h, ~y=v, ~blur=blur, ~spread=spread, color)
    |])]
  ),
  (
    [%expr [%css "box-shadow: 10px 10px 0px $(spread) $(color);"]],
    [%expr CssJs.boxShadows([|
      CssJs.Shadow.box(
        ~x=`pxFloat(10.),
        ~y=`pxFloat(10.),
        ~blur=`pxFloat(0.),
        ~spread=spread,
        color
      )
    |])]
  ),
  /* Add border */
  /* Add text-shadow */
];

describe("Should bind to bs-css with interpolatated variables", ({test, _}) => {
  properties_variable_css_tests |>
    List.iteri((index, (result, expected)) =>
      test(
        "simple variable: " ++ string_of_int(index),
        compare(result, expected),
      )
    );
});
