open Setup;
open Reason_css_parser;
open Parser;

let test = (parser, input, output) => (
  input,
  ({expect, _}) => {
    let parse = parse(parser);
    let received = parse(input);
    switch (received) {
    | Error(message) => print_endline(message)
    | _ => ()
    };
    expect.result(received).toBe(Ok(output));
  },
);

let tests = [
  test(
    [%value "<rgb()>"],
    "rgb(.5 .3 10 / 1)",
    `Rgb_1(([0.5, 0.3, 10.0], Some(((), `Number(1.0))))),
  ),
  test(
    [%value "<rgb()>"],
    "rgb(.6, .4, 5)",
    `Rgb_3(([0.6, 0.4, 5.0], None)),
  ),
  test(
    [%value "<rgba()>"],
    "rgba(25% 33% 44% / 0.6)",
    `Rgba_0(([25.0, 33.0, 44.0], Some(((), `Number(0.6))))),
  ),
  test(
    [%value "<rgba()>"],
    "rgba(2.5, 3.3, 4.4, 60%)",
    `Rgba_3(([2.5, 3.3, 4.4], Some(((), `Percentage(60.0))))),
  ),
  test(
    [%value "<rgba()>"],
    "rgba(2.5, 3.3, 4.4, 0.5)",
    `Rgba_3(([2.5, 3.3, 4.4], Some(((), `Number(0.5))))),
  ),
];

describe("Parser", ({test, _}) => {
  tests |> List.iter(((input, test_fn)) => test(input, test_fn))
});
